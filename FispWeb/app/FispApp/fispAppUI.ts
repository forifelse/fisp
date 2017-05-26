namespace Fisp
{
    export class DlgTop extends IWnd {
        mUiMgr: UIMgr;
        mmainBtn: UIButton;
        mtexLogo: UITexture;
        mTextFPS: UIText;
        mTextWSS: UIText;
        mdlgMain: DlgMain;

        constructor(uiMgr) {
            super('dlgtop');
            this.mUiMgr = uiMgr;
            this.build(true);
        }

        build(bReBuild = false) {
            if (bReBuild) {
                if (this.mmainBtn) {
                    this.mmainBtn.setVisible(false, false);
                    this.mmainBtn.dispose();
                }
                if (this.mtexLogo) {
                    this.mtexLogo.setVisible(false, false);
                    this.mtexLogo.dispose();
                }
            }
            var that = this;
            var clickLogo = function () {
                var bShow = (that.mdlgMain) ? (!that.mdlgMain.isVisible()) : false;
                that.mdlgMain.show(bShow);
            };
            var cvsSize = this.mUiMgr.getCanvasSize();
            var opt = UIStyle.button((cvsSize.width / 2 - 32), (cvsSize.height - 64), 64, 64, "", gRoot.mCfg.mstrDataPath + "source/logo.png", "white", "black", "0px");
            this.mmainBtn = new UIButton("mainmenu", opt, this.mUiMgr, clickLogo, true);
        }

        resize(evt) {
            if (null != this.mmainBtn) {
                var cvsSize = this.mUiMgr.getCanvasSize();
                this.mmainBtn.resize((cvsSize.width / 2 - 32), (cvsSize.height - 64), 64, 64);
            }
        }

        exchangeUILang(lang: number) {
            this.mmainBtn.value = gLang.mmainMenu[lang];
            //this.mTextFPS = ;
            //this.mTextWSS = ;
        }

    }

    export class DlgMain extends IWnd {
        mUiMgr: UIMgr;
        mdlg: UIWindow;
        mLgc: FispApp;
        mbFullsceen: boolean;

        constructor(uiMgr, bShow = true) {
            super('dlgmain');
            this.mUiMgr = uiMgr;
            this.mbFullsceen = false;
            this.build(bShow);
        }

        build(bShow = false) {
            var lang = gLang.muLang;
            var barSize = 64;
            var cvsSize = this.mUiMgr.getCanvasSize();
            var cx = 300;
            var cy = Math.min(500, cvsSize.height - 2 * barSize);
            var x = 0.5 * (cvsSize.width - cx);
            var y = 0.5 * (cvsSize.height - barSize - cy);
            var textTitle = gLang.mmainMenu[lang];
            var opt = UIStyle.window(x, y, cx, cy, textTitle);
            this.mdlg = new UIWindow(this.mstrWndName, opt, this.mUiMgr);
            this.mdlg.setVisible(bShow, true);
            //
            var that = this;
            var user = gUser.mbSignin ? gUser.mstrName : "";
            var ypos = 40;
            var scecnt = 0;
            var pubed = 0;
            {
                var opt = UIStyle.text(0, ypos, gLang.mWelcome[lang] + "  " + user, 16, 'rgba(255,255,0,1.0)');
                var txt = new UIText("welcome", opt, this.mUiMgr, false);
                this.mdlg.add(txt);
                txt.setVisible(false, false);
                var opt = UIStyle.text(0, ypos + 25, "", 16);
                var txt = new UIText("sceneInfo", opt, this.mUiMgr, false);
                this.mdlg.add(txt);
                txt.setVisible(false, false);
                var opt = UIStyle.button(20, ypos + 55, 100, 30, gLang.mSignout[lang]);
                var fun = function (e) { gUser.signout(); that.signState(false); that.exchangeUILang(gLang.muLang); };
                var btn = new UIButton("btnSignout", opt, this.mUiMgr, fun, false);
                this.mdlg.add(btn);
                btn.setVisible(false, false);
                var opt = UIStyle.button(125, ypos + 55, 100, 30, gLang.mUserinfo[lang]);
                var fun = function (e) { gMsgbox.showMsg(gUser.mstrName + " Scene " + scecnt + ", Published: " + pubed, that.mdlg); this.mDlg.setVisible(false); };
                var btn = new UIButton("btnUserinfo", opt, this.mUiMgr, fun, false);
                this.mdlg.add(btn);
                btn.setVisible(false, false);
            }
            {
                var opt = UIStyle.text(0, ypos, gLang.minName[lang], 16);
                var txt = new UIText("labid", opt, this.mUiMgr, false);
                this.mdlg.add(txt);
                var opt = UIStyle.text(0, ypos + 27, gLang.minPswd[lang], 16);
                var txt = new UIText("labpw", opt, this.mUiMgr, false);
                this.mdlg.add(txt);
                var opt = UIStyle.edit(70, ypos, 160, 20, "");
                var edtid = new UITextEdit("edtid", opt, this.mUiMgr, null, false);
                this.mdlg.add(edtid);
                var opt = UIStyle.edit(70, ypos + 27, 160, 20, "", "password");
                var edtpw = new UITextEdit("edtpw", opt, this.mUiMgr, null, false);
                this.mdlg.add(edtpw);
                var opt = UIStyle.button(20, ypos + 55, 100, 30, gLang.mSignin[lang]);
                var fun = function (e) {
                    if (edtid.getValue() == '' || edtpw.getValue() == '') {
                        gMsgbox.showMsg(gLang.mString.msg.canotempty[gLang.muLang], that.mdlg);
                    } else {
                        gUser.signin(edtid.getValue(), edtpw.getValue()); edtpw.setValue("");
                    }
                };
                var btn = new UIButton("btnSignin", opt, this.mUiMgr, fun, false);
                this.mdlg.add(btn);
                var opt = UIStyle.button(125, ypos + 55, 100, 30, gLang.mSignup[lang]);
                var fun = function (e) {
                    edtid.setValue(''); edtpw.setValue(''); that.mdlg.setVisible(false);
                    var dlg = that.mUiMgr.findUserDlg('dlgsignup');
                    if (!dlg) {
                        dlg = new Fisp.DlgSignup(that.mUiMgr, true);
                        that.mUiMgr.regUserDlg(dlg);
                    }
                    (<DlgSignup>dlg).mdlg.setVisible(true);
                };
                var btn = new UIButton("btnSignup", opt, this.mUiMgr, fun, false);
                this.mdlg.add(btn);
            }
            var opt = UIStyle.button(240, ypos, 60, 20, gLang.mlang[lang]);
            var btn = new UIButton("btnlang", opt, this.mUiMgr, function () { that.exchangeAllUILang(gLang.shift()); }, false);
            this.mdlg.add(btn);
            var opt = UIStyle.button(240, ypos + 27, 60, 20, gLang.mHelp[lang]);
            var fun = function (e) { gMsgbox.showMsg(gLang.mMsgHelp[lang], that.mdlg); that.mdlg.setVisible(false, false); }
            var btn = new UIButton("btnhelp", opt, this.mUiMgr, fun, false);
            this.mdlg.add(btn);
            var opt = UIStyle.button(240, ypos + 54, 60, 20, gLang.mString.dlgMain.chat[lang]);
            var fun = function (e) { var dlg: DlgChat = that.mUiMgr.findUserDlg('dlgchat'); dlg.mdlg.setVisible(!dlg.isVisible()); }
            var btn = new UIButton("btnChat", opt, this.mUiMgr, fun, false);
            this.mdlg.add(btn);
            //
            var opt = UIStyle.button(30, ypos + 100, 240, 50, gLang.mFullscreen[lang]);
            var btn = new UIButton("btnFullscreen", opt, this.mUiMgr, function (e) { that.fullscreen(e); that.show(false); }, false);
            this.mdlg.add(btn);

            var opt = UIStyle.button(30, ypos + 160, 240, 50, gLang.mHideEditor[lang]);
            var fun = function (e) {
                var dlg: DlgEditScene = that.mUiMgr.findUserDlg('dlgeditscene');
                if (gUser.mbEdit) {
                    that.mdlg.find('btnPlay').innerHTML = gLang.mShowEditor[gLang.muLang];
                    that.closeAllEditDlg();
                    dlg.mdlg.setVisible(false);
                    //gRoot.mFrame.mLgc.exitEdit();
                    //gRoot.mFrame.mLgc.editMode(false);
                }
                else {
                    that.mdlg.find('btnPlay').innerHTML = gLang.mHideEditor[gLang.muLang];
                    dlg.mdlg.setVisible(true);
                    //var b = gRoot.mFrame.mLgc.editScene();
                    //if (b) { gRoot.mFrame.mLgc.editMode(true); }
                }
                gUser.mbEdit = !gUser.mbEdit;
            };
            var btn = new UIButton("btnPlay", opt, this.mUiMgr, fun, false);
            this.mdlg.add(btn);
            //
            var opt = UIStyle.button(30, ypos + 220, 240, 50, gLang.mRunVR[lang]);
            var funRun = function (e) {
                that.show(false);
                Utility.downloadFile("VR-exe.rar");
                //Utility.runExe("file:///F:/UE4SrcBuild/fisp/x64/Release/cyhsEXE.exe");
            }
            var btn = new UIButton("btnRunVR", opt, this.mUiMgr, funRun, false);
            this.mdlg.add(btn);
            var opt = UIStyle.button(30, ypos + 280, 240, 50, gLang.mRunMR[lang]);
            var fun = function (e) { that.mdlg.setVisible(false, false); Utility.downloadFile("MR-exe.rar"); };
            var btn = new UIButton("btnRunMR", opt, this.mUiMgr, fun, false);
            this.mdlg.add(btn);
            //
            var opt = UIStyle.button(cx - 30, 0, 30, 30, "X", null, "white", "rgba(200,4,4,1.0)");
            var fun = function (e) { that.mdlg.setVisible(false, false); };
            var btn = new UIButton("maindlgclose", opt, this.mUiMgr, fun, false);
            this.mdlg.add(btn);
        }

        destroy() {
            if (this.mdlg) {
                this.mdlg.setVisible(false, false);
                this.mdlg.dispose();
            }
            this.mdlg = null;
        }

        show(bShow) {
            if (!this.mdlg) {
                if (bShow) {
                    this.build(bShow);
                }
            }
            else {
                this.mdlg.setVisible(bShow, false);
            }
        }

        isVisible() {
            var bVisible = (this.mdlg) ? this.mdlg.isVisible() : false;
            return bVisible;
        }

        signState(signed: boolean) {
            var display = signed ? "none" : "block";
            this.mdlg.find('labid').style.display = display;
            this.mdlg.find('labpw').style.display = display;
            this.mdlg.find('edtid').style.display = display;
            this.mdlg.find('edtpw').style.display = display;
            this.mdlg.find('btnSignin').hidden = signed;
            this.mdlg.find('btnSignup').hidden = signed;
            //
            var display = signed ? "block" : "none";
            this.mdlg.find('welcome').innerHTML = gLang.mString.msg.welcome[gLang.muLang] + ': ' + gUser.mstrName + '!';
            this.mdlg.find('sceneInfo').innerHTML = gLang.mSceneCnt[gLang.muLang] + ": " + gUser.sceneCnt();;
            this.mdlg.find('welcome').style.display = display;
            this.mdlg.find('sceneInfo').style.display = display;
            this.mdlg.find('btnSignout').style.display = display;
            this.mdlg.find('btnUserinfo').style.display = display;
            //
            this.mdlg.find('edtid').innerHTML = '';
            this.mdlg.find('edtid').innerText = '';
            this.mdlg.find('edtid').nodeValue = '';
        }

        resize(evt) {
            //var bVisible = this.isVisible();
            //this.destroy();
            //this.build(bVisible);
            //var lang = gLang.muLang;
            //var str = (this.mbFullsceen) ? gLang.mWindowMode[lang] : gLang.mFullscreen[lang];
            //this.mdlg.getElementById("fullscreen").innerText = str;
        }

        fullscreen(evt: Event) {
            //this.mdlg.setVisible(false, false);
            this.mbFullsceen = !this.mbFullsceen;
            //gRoot.mFrame.mInput.fullscreen(this.mbFullsceen);
            Fisp.FispRoot.fullscreen(this.mbFullsceen);
            var lang = gLang.muLang;
            var str = (this.mbFullsceen) ? gLang.mWindowMode[lang] : gLang.mFullscreen[lang];
            this.mdlg.getElementById("btnFullscreen").innerHTML = str;
            if (this.mbFullsceen) {
                gRoot.mFrame.onResize(evt);
            }
        }

        exchangeUILang(lang: number) {
            this.mdlg.titleWnd().innerHTML = gLang.mmainMenu[lang];
            this.mdlg.find('labid').innerHTML = gLang.minName[lang];
            this.mdlg.find('labpw').innerHTML = gLang.minPswd[lang];
            this.mdlg.find('btnlang').innerHTML = gLang.mlang[lang];
            this.mdlg.find('btnhelp').innerHTML = gLang.mHelp[lang];
            this.mdlg.find('btnChat').innerHTML = gLang.mString.dlgMain.chat[lang];
            if (gUser.mbSignin) {
                this.mdlg.find('welcome').innerHTML = gLang.mString.msg.welcome[lang] + ": " + gUser.mstrName + "!";
                this.mdlg.find('sceneInfo').innerHTML = gLang.mSceneCnt[lang] + ": " + gUser.sceneCnt();
                this.mdlg.find('btnSignout').innerHTML = gLang.mSignout[lang];
                this.mdlg.find('btnUserinfo').innerHTML = gLang.mUserinfo[lang];
            }
            else {
                this.mdlg.find('btnSignin').innerHTML = gLang.mSignin[lang];
                this.mdlg.find('btnSignup').innerHTML = gLang.mSignup[lang];
            }
            this.mdlg.find('btnFullscreen').innerHTML = this.mbFullsceen ? gLang.mWindowMode[lang] : gLang.mFullscreen[lang];
            this.mdlg.find('btnPlay').innerHTML = gUser.mbEdit ? gLang.mHideEditor[lang] : gLang.mShowEditor[lang];
            this.mdlg.find('btnRunVR').innerHTML = gLang.mRunVR[lang];
            this.mdlg.find('btnRunMR').innerHTML = gLang.mRunMR[lang];
        }

        exchangeAllUILang(lang: number) {
            var dlg = null;
            var cnt = this.mUiMgr.userData.dlgList.length;
            for (var i = 0; i < cnt; i++) {
                dlg = this.mUiMgr.userData.dlgList[i];
                if (dlg && dlg.exchangeUILang) {
                    dlg.exchangeUILang(lang);
                }
            }
        }

        closeAllEditDlg() {
        }

        showSettingDlg(bShow) {
        }

        // auxi
        fillSelectCtrl(jsStr, selCtrl) {
            if (!jsStr || !selCtrl) { return; }
            var jsList = JSON.parse(jsStr);
            var cnt = jsList.list.length;
            for (var i = 0; i < cnt; i++) {
                selCtrl.addOptions(jsList.list[i], jsList.list[i]);
            }
        }

    }

    export class DlgSignup extends IWnd {
        mUiMgr: UIMgr;
        mdlg: UIWindow;

        constructor(uiMgr, bShow = true) {
            super('dlgsignup');
            this.mUiMgr = uiMgr;
            this.build(bShow);
        }

        build(bShow = false) {
            var lang = gLang.muLang;
            var barSize = 64;
            var cvsSize = this.mUiMgr.getCanvasSize();
            var cx = 240;
            var cy = 200;//Math.min(500, cvsSize.height - 2 * barSize);
            var x = 0.5 * (cvsSize.width - cx);
            var y = 0.5 * (cvsSize.height - barSize - cy);
            var textTitle = gLang.mString.dlgSignup.title[lang];
            var opt = UIStyle.window(x, y, cx, cy, textTitle);
            this.mdlg = new UIWindow(this.mstrWndName, opt, this.mUiMgr);
            this.mdlg.setVisible(bShow, true);
            //
            var that = this;
            var user = gUser.mbSignin ? gUser.mstrName : "";
            var ypos = 40;
            var scecnt = 0;
            var pubed = 0;
            {
                var opt = UIStyle.text(0, ypos, gLang.minName[lang], 16);
                var txt = new UIText("labid_r", opt, this.mUiMgr, false);
                this.mdlg.add(txt);
                var opt = UIStyle.text(0, ypos + 27, gLang.minPswd[lang], 16);
                var txt = new UIText("labpw_r", opt, this.mUiMgr, false);
                this.mdlg.add(txt);
                var opt = UIStyle.text(0, ypos + 54, gLang.mString.dlgSignup.repeadpw[lang], 16);
                var txt = new UIText("labpwRep", opt, this.mUiMgr, false);
                this.mdlg.add(txt);
                var opt = UIStyle.text(0, ypos + 81, gLang.mString.dlgSignup.email[lang], 16);
                var txt = new UIText("labemail", opt, this.mUiMgr, false);
                this.mdlg.add(txt);
                //
                var opt = UIStyle.edit(70, ypos, 160, 20, "");
                var edtid = new UITextEdit("edtid_r", opt, this.mUiMgr, null, false);
                this.mdlg.add(edtid);
                var opt = UIStyle.edit(70, ypos + 27, 160, 20, "", "password");
                var edtpw = new UITextEdit("edtpw_r", opt, this.mUiMgr, null, false);
                this.mdlg.add(edtpw);
                var opt = UIStyle.edit(70, ypos + 54, 160, 20, "", "password");
                var edtpwR = new UITextEdit("edtpwRep", opt, this.mUiMgr, null, false);
                this.mdlg.add(edtpwR);
                var opt = UIStyle.edit(70, ypos + 81, 160, 20, "");
                var edtemail = new UITextEdit("edtemail", opt, this.mUiMgr, null, false);
                this.mdlg.add(edtemail);
                var opt = UIStyle.button(40, ypos + 115, 160, 30, gLang.mSignup[lang]);
                var fun = function (e) {
                    if (edtid.getValue() == '' || edtpw.getValue() == '' || edtpwR.getValue() == '') {
                        gMsgbox.showMsg(gLang.mString.msg.canotempty[gLang.muLang], that.mdlg);
                    }
                    else {
                        if (edtpw.getValue() == edtpwR.getValue()) {
                            var opt: any = new Object();
                            opt.email = edtemail.getValue();
                            gUser.signup(edtid.getValue(), edtpw.getValue(), opt);
                            edtid.setValue('');
                            edtpw.setValue('');
                            edtpwR.setValue('');
                            edtemail.setValue('');
                        }
                        else {
                            gMsgbox.showMsg(gLang.mString.msg.signupPWMismatch[gLang.muLang], that.mdlg);
                        }
                    }
                };
                var btn = new UIButton("btnSignup_r", opt, this.mUiMgr, fun, false);
                this.mdlg.add(btn);
            }
            //
            var opt = UIStyle.button(cx - 30, 0, 30, 30, "X", null, "white", "rgba(200,4,4,1.0)");
            var fun = function (e) { that.mdlg.setVisible(false, false); (<DlgMain>that.mUiMgr.findUserDlg('dlgmain')).mdlg.setVisible(true); };
            var btn = new UIButton("signupdlgclose", opt, this.mUiMgr, fun, false);
            this.mdlg.add(btn);
        }

        destroy() {
            if (this.mdlg) {
                this.mdlg.setVisible(false, false);
                this.mdlg.dispose();
            }
            this.mdlg = null;
        }

        show(bShow) {
            if (!this.mdlg) {
                if (bShow) {
                    this.build(bShow);
                }
            }
            else {
                this.mdlg.setVisible(bShow, false);
            }
        }

        isVisible() {
            var bVisible = (this.mdlg) ? this.mdlg.isVisible() : false;
            return bVisible;
        }

        exchangeUILang(lang: number) {
            this.mdlg.titleWnd().innerHTML = gLang.mString.dlgSignup.title[lang];
            this.mdlg.find('labid_r').innerHTML = gLang.minName[lang];
            this.mdlg.find('labpw_r').innerHTML = gLang.minPswd[lang];
            this.mdlg.find('labpwRep').innerHTML = gLang.mString.dlgSignup.repeadpw[lang];
            this.mdlg.find('labemail').innerHTML = gLang.mString.dlgSignup.email[lang];
            this.mdlg.find('btnSignup_r').innerHTML = gLang.mSignup[lang];
        }

    }

    //
    export class DlgChat extends IWnd {
        mUiMgr: UIMgr;
        mdlg: UIWindow;
        mChat: UITextArea;

        constructor(uiMgr, bShow = true) {
            super('dlgchat');
            this.mUiMgr = uiMgr;
            this.build(bShow);
        }

        build(bShow = false) {
            var lang = gLang.muLang;
            var barSize = 64;
            var cvsSize = this.mUiMgr.getCanvasSize();
            var cx = 400;
            var cy = (cvsSize.height < this.mUiMgr.heightThreshold()) ? 200 : 240;//Math.min(500, cvsSize.height - 2 * barSize);
            var x = 2;
            var y = cvsSize.height - cy - 2;
            var textTitle = gLang.mString.dlgChat.title[lang];
            var opt = UIStyle.window(x, y, cx, cy, textTitle);
            this.mdlg = new UIWindow(this.mstrWndName, opt, this.mUiMgr);
            this.mdlg.setVisible(bShow, true);
            //
            var that = this;
            var user = gUser.mbSignin ? gUser.mstrName : "Vistor";
            var ypos = 35;
            {
                var opt = UIStyle.editArea(1, ypos, 5, 40, "", 16, true);
                var fun = function (e) { };
                this.mChat = new UITextArea("edtChat", opt, this.mUiMgr, fun, false);
                this.mdlg.add(this.mChat);
                var opt = UIStyle.editArea(1, ypos + 136, 2, 32, "", 16);
                var edtSend = new UITextArea("edtSend", opt, this.mUiMgr, null, false);
                this.mdlg.add(edtSend);
                var opt = UIStyle.button(cx - 65, ypos + 160, 60, 30, gLang.mString.dlgChat.send[lang]);
                var fun = function (e) {
                    var msg = edtSend.getValue();
                    if (msg && msg.length > 0) {
                        gUser.sendMsg(msg);
                        edtSend.setValue('');
                    }
                    else
                        gMsgbox.showMsg(gLang.mString.msg.chatEmpty[gLang.muLang], null);
                };
                var btn = new UIButton("btnChatSend", opt, this.mUiMgr, fun, false);
                this.mdlg.add(btn);
            }
            //
            var opt = UIStyle.button(cx - 30, 0, 30, 30, "X", null, "white", "rgba(200,4,4,1.0)");
            var fun = function (e) { that.mdlg.setVisible(false, false); };
            var btn = new UIButton("signupdlgclose", opt, this.mUiMgr, fun, false);
            this.mdlg.add(btn);
        }

        destroy() {
            if (this.mdlg) {
                this.mdlg.setVisible(false, false);
                this.mdlg.dispose();
            }
            this.mdlg = null;
        }

        show(bShow) {
            if (!this.mdlg) {
                if (bShow) {
                    this.build(bShow);
                }
            }
            else {
                this.mdlg.setVisible(bShow, false);
            }
        }

        isVisible() {
            var bVisible = (this.mdlg) ? this.mdlg.isVisible() : false;
            return bVisible;
        }

        exchangeUILang(lang: number) {
            this.mdlg.titleWnd().innerHTML = gLang.mString.dlgChat.title[lang];
            this.mdlg.find('btnChatSend').innerHTML = gLang.mString.dlgChat.send[lang];
        }

    }

    //
    export class DlgEditScene extends IWnd {
        mUiMgr: UIMgr;
        mdlg: UIWindow;
        mvOpt: Array<UIButton>;
        mvPnl: Array<UIPanel>;
        miSel: number;

        constructor(uiMgr, bShow: boolean = true, idxOpt: number = 0) {
            super('dlgeditscene');
            this.mUiMgr = uiMgr;
            this.build(true);
        }

        build(bShow: boolean = true, idxOpt: number = 0) {
            var lang = gLang.muLang;
            var cx = 300;
            var cvsSize = this.mUiMgr.getCanvasSize();
            var cy = 340;//(cvsSize.height < this.mUiMgr.heightThreshold()) ? 240 : 340;//cvsSize.height - 200;
            var x = 2; var y = 0;
            var opt = UIStyle.window(x, y, cx, cy, gLang.mSceneOp[lang]);
            this.mdlg = new UIWindow(this.mstrWndName, opt, this.mUiMgr);
            this.mdlg.setVisible(bShow);
            //
            var opt = UIStyle.text(0, 32, gLang.mScene[lang] + ":  ", 16);
            var txt = new UIText("editSceneName", opt, this.mUiMgr, false);
            this.mdlg.add(txt);
            var cursce = (gUser.curScene().length > 0) ? gUser.curScene() : " ";
            var opt = UIStyle.text(50, 32, cursce, 16, 'yellow');
            var txt = new UIText("editCurSceneName", opt, this.mUiMgr, false);
            this.mdlg.add(txt);
            //
            var that = this;
            var opt = UIStyle.option(4, 55, 70, 30, gLang.moptScene[lang]);
            var fun = function (e) { that.clickEditOpt(0); that.resizeOptBtn(e.target, 30); };
            var btn0 = new UIButton("editsce", opt, this.mUiMgr, fun, false);
            that.mdlg.add(btn0);
            var opt = UIStyle.option(78, 55, 70, 30, gLang.moptPlace[lang]);
            var fun = function (e) { that.clickEditOpt(1); that.resizeOptBtn(e.target, 30); };
            var btn1 = new UIButton("editpla", opt, this.mUiMgr, fun, false);
            this.mdlg.add(btn1);
            var opt = UIStyle.option(152, 55, 70, 30, gLang.moptTerrain[lang]);
            var fun = function (e) { that.clickEditOpt(2); that.resizeOptBtn(e.target, 30); };
            var btn2 = new UIButton("editterr", opt, this.mUiMgr, fun, false);
            this.mdlg.add(btn2);
            var opt = UIStyle.option(226, 55, 70, 30, gLang.moptFoliage[lang]);
            var fun = function (e) { that.clickEditOpt(3); that.resizeOptBtn(e.target, 30); };
            var btn3 = new UIButton("editfol", opt, this.mUiMgr, fun, false);
            this.mdlg.add(btn3);
            this.mvOpt = [btn0, btn1, btn2, btn3];
            this.mvPnl = [null, null, null, null];
            this.miSel = idxOpt;
            this.clickEditOpt(idxOpt);
            //
            var opt = UIStyle.button(270, 0, 30, 30, "X", null, "white", "rgba(200,4,4,1.0)");
            var fun = function (e) { that.mdlg.setVisible(false); gUser.mbEdit = false; var dlg: DlgEditScene = that.mUiMgr.findUserDlg('dlgmain'); dlg.mdlg.find('btnPlay').innerHTML = gLang.mShowEditor[gLang.muLang]; }
            var btn = new UIButton("editsceneclose", opt, this.mUiMgr, fun, false);
            this.mdlg.add(btn);
        }

        clickEditOpt(selIdx) {
            var cnt = (this.mvPnl) ? this.mvPnl.length : 0;
            for (var i = 0; i < cnt; i++) {
                if (selIdx == i && !this.mvPnl[i]) {
                    switch (selIdx) {
                        case 0:
                            this.showScePnl(true, true);
                            break;
                        case 1:
                            this.showPlaPnl(true, true); break;
                        case 2:
                            this.showTerrPnl(); break;
                        case 3:
                            this.showFoliPnl(); break;
                        default:
                            this.showScePnl(true, true);
                    }
                }
                //
                if (this.mvPnl[i]) {
                    var bShow = (selIdx == i);
                    this.mvPnl[i].setVisible(bShow);
                    if (bShow) {
                        this.miSel = selIdx;
                    }
                }
            }
        }

        resizeOptBtn(btn: HTMLElement, defSize: number) {
            for (var i = 0; i < this.mvOpt.length; i++) {
                this.mdlg.resize(this.mvOpt[i].id, -1, defSize);
            }
            btn.style.height = (defSize + 6) + 'px';
        }

        showScePnl(bShow, bReCreate) {
            var pos = [];
            var idx = 0;
            if (this.mvPnl && this.mvPnl[idx]) {
                if (bReCreate) {
                    pos.push(this.mvPnl[idx].divPosition.x);
                    pos.push(this.mvPnl[idx].divPosition.y);
                    this.mvPnl[idx].setVisible(false);
                    //this.mvPnl[idx].dispose(); 
                    var ele = this.mdlg.getElementById("editscepnl");
                    if (ele && ele.remove) { ele.remove(); }
                }
                else {
                    this.mvPnl[idx].setVisible(bShow);
                    return;
                }
            }
            var lang = gLang.muLang;

            var py = this.mdlg.windowSize.height - 90;
            var opt = UIStyle.panel(2, 50, 296, py);
            var pnl = new UIPanel("editscepnl", opt, this.mUiMgr, null, false);
            this.mdlg.add(pnl);
            pnl.setVisible(true);

            var that = this;
            var sx = 0; var sy = 0;
            var cnt = gUser.sceneCnt();
            if (cnt > 0) {
                var col = 4;
                var row = Math.ceil(cnt / col);
                var k = 0;
                var yOff = 5;
                var strTxt = "";
                for (var i = 0; i < row; i++) {
                    for (var j = 0; j < col && (i * col + j < cnt); j++ , k++) {
                        var str = gUser.sceneName[k];
                        if (Fisp.Utility.strLength(str) > 6) {
                            strTxt = str.substr(0, 6) + "...";
                        }
                        else {
                            strTxt = str;
                        }
                        sx = j * (64 + 6);
                        sy = i * (64 + 6) + yOff;
                        var opt = UIStyle.text(sx, sy + 45, strTxt, 16);
                        var txt = new UIText("scene" + k, opt, this.mUiMgr, false);
                        var clickImg = function (e) { }//{ that.selectSceneByImgTag(e.target); };
                        pnl.add(txt);
                        var img = new UITexture(str, gRoot.mCfg.mstrDataPath + "source/leaf0.png", { w: 64, h: 64, x: j * (64 + 6), y: i * (64 + 6) + yOff }, this.mUiMgr, clickImg, false);
                        pnl.add(img);
                        var opt = UIStyle.button(j * (64 + 6), i * (64 + 6) + yOff, 64, 64, " ", null, "rgba(0,0,0,0.0)", "1px", "1px");
                        var btn = new UIButton(str, opt, this.mUiMgr, clickImg, false);
                        pnl.add(btn);
                    }
                }
            }
            var py = Math.max(sy + 80, pnl.divSize.height - 105);
            var opt = UIStyle.edit(1, py, 170, 25, gLang.mNewScene[lang]);
            var txtscename = new UITextEdit("editscename", opt, this.mUiMgr, null, false);
            pnl.add(txtscename);
            var opt = UIStyle.button(180, py, 90, 30, gLang.mNewScene[lang]);
            var fun = function () {
                if (txtscename.getValue() && txtscename.getValue().length > 0) {
                    if (gUser.findScene(txtscename.getValue())) {
                        gMsgbox.showMsg(gLang.mString.msg.nameexist[gLang.muLang]);
                    } else {
                        var cnt = gUser.sceneCnt();
                        if (cnt < 8) {
                            gUser.newScene(txtscename.getValue());
                            that.newScene(cnt, txtscename.getValue());
                        } else {
                            gMsgbox.showMsg(gLang.mString.msg.sceneAtMax[gLang.muLang]);
                        }
                    }
                } else {
                    gMsgbox.showMsg(gLang.mString.msg.nameempty[gLang.muLang]);
                }
            };
            var btn = new UIButton("editscenew", opt, this.mUiMgr, fun, false);
            pnl.add(btn);
            //
            py += 35;
            var opt = UIStyle.text(1, py, gLang.mMultiuser[lang], 16);
            var txt = new UIText("txtsceneopgroup", opt, this.mUiMgr, false);
            pnl.add(txt);
            var opt = UIStyle.checkbox(90, py, 1.5);
            var che = new UICheckbox("chesceneopgroup", opt, this.mUiMgr, null, false);
            pnl.add(che);
            var opt = UIStyle.text(140, py, gLang.mPublishScene[lang], 16);
            var txt = new UIText("txtsceneoppub", opt, this.mUiMgr, false);
            pnl.add(txt);
            var opt = UIStyle.checkbox(240, py, 1.5);
            var che = new UICheckbox("chesceneoppub", opt, this.mUiMgr, null, false);
            pnl.add(che);
            //
            py += 35;
            var opt = UIStyle.button(0, py, 65, 30, gLang.mJoin[lang]);
            var btn = new UIButton("editsceexport", opt, this.mUiMgr, null, false);
            pnl.add(btn);
            var opt = UIStyle.button(69, py, 65, 30, gLang.mUpdate[lang]);
            var btn = new UIButton("editsceupdate", opt, this.mUiMgr, null, false);
            pnl.add(btn);
            var opt = UIStyle.button(138, py, 65, 30, gLang.mSave[lang]);
            var fun = function () { }//{ var jsSave = Fisp.mcScene.saveToJS(); Fisp.mcAuxi.putFile("data/jssave/jssave.json", jsSave); Fisp.mcSocket.sendMsg("savescene"); };
            var btn = new UIButton("editscesave", opt, this.mUiMgr, fun, false);
            pnl.add(btn);
            var opt = UIStyle.button(207, py, 65, 30, gLang.mDelete[lang]);
            var fun = function () { that.delAllSceneItem(); var idx = gUser.delScene(); that.updateSceneItem(idx, gUser.curScene()); };//{ gRoot.mFrame.mLgc.delScene(); };
            var btn = new UIButton("editscedel", opt, this.mUiMgr, fun, false);
            pnl.add(btn);
            //
            if (this.mvPnl && this.mvPnl.length > idx) {
                this.mvPnl[idx] = pnl;
            }
            return pnl;
        }

        selectSceneByImgTag(imgCtrl) {
            var ctrlid = imgCtrl.id;
            var bOk = this.selectSceneByName(ctrlid);
        }

        selectSceneByName(name) {
            var bOk = false;
            var tail = '_scenebtn';
            gUser.midxScene = -1;
            if (name && name.length > 0) {
                //var cnt = gUser.mvSceneName.length;
                var cnt = gUser.mUserData.mSceneList.length;
                for (var i = 0; i < cnt; i++) {
                    //if (name == gUser.mvSceneName[i]) {
                    if (name == gUser.mUserData.mSceneList[i] + tail) {
                        gUser.midxScene = i;
                        name = gUser.mUserData.mSceneList[i];
                        gUser.mstrCurScene = name;
                        bOk = true;
                        break;
                    }
                }
            }
            this.mdlg.getElementById("editCurSceneName").innerText = bOk ? name : "";
            if (bOk) {
                //App.appUi.mdlgEditProperty.clearEntity();
            }
            return bOk;
        }

        selectSceneByIdx(idx: number) {
            var name = (idx >= 0 && idx < gUser.sceneCnt()) ? gUser.sceneName(idx) : "";
            this.mdlg.getElementById("editCurSceneName").innerText = name;
        }

        showPlaPnl(bShow, bReCreate, idxType = 0) {
            var pos = [];
            var idx = 1;
            if (this.mvPnl && this.mvPnl[idx]) {
                if (bReCreate) {
                    pos.push(this.mvPnl[idx].divPosition.x);
                    pos.push(this.mvPnl[idx].divPosition.y);
                    this.mvPnl[idx].setVisible(false);
                    //this.mvPnl[idx].dispose(); 
                    var ele = this.mdlg.getElementById("editplapnl");
                    if (ele && ele.remove) { ele.remove(); }
                }
                else {
                    this.mvPnl[idx].setVisible(bShow);
                    this.clickPlaceSubOpt(idxType);
                    return;
                }
            }
            var lang = gLang.muLang;
            var that = this;

            var py = this.mdlg.windowSize.height - 90;
            var opt = UIStyle.panel(2, 50, 296, py);
            var pnl = new UIPanel("editplapnl", opt, this.mUiMgr, null, false);
            this.mdlg.add(pnl);
            pnl.setVisible(true);
            this.mvPnl[idx] = pnl;

            var yOff = 5;
            var opt = UIStyle.option(1, 10, 70, 25, gLang.mGlobal[lang]);
            var fun = function (e) { that.clickPlaceSubOpt(0); };
            var btn = new UIButton("editplaglobal", opt, this.mUiMgr, fun, false);
            pnl.add(btn);
            var opt = UIStyle.option(1, 35, 70, 25, gLang.mBasic[lang]);
            var fun = function (e) { that.clickPlaceSubOpt(1); };
            var btn = new UIButton("editplabasic", opt, this.mUiMgr, fun, false);
            pnl.add(btn);
            var opt = UIStyle.option(1, 60, 70, 25, gLang.mBuild[lang]);
            var fun = function (e) { that.clickPlaceSubOpt(2); };
            var btn = new UIButton("editplabuild", opt, this.mUiMgr, fun, false);
            pnl.add(btn);
            var opt = UIStyle.option(1, 85, 70, 25, gLang.mMachine[lang]);
            var fun = function (e) { that.clickPlaceSubOpt(3); };
            var btn = new UIButton("editplamachine", opt, this.mUiMgr, fun, false);
            pnl.add(btn);
            //
            pnl.userData.mvSubpnl = [null, null, null, null];
            pnl.userData.mvSubpnlIdx = -1;
            this.clickPlaceSubOpt(idxType);
            return pnl;
        }

        clickPlaceSubOpt(selidx) {
            var cnt = (this.mvPnl[1] && this.mvPnl[1].userData.mvSubpnl) ? this.mvPnl[1].userData.mvSubpnl.length : 0;
            for (var i = 0; i < cnt; i++) {
                if (selidx == i && !this.mvPnl[1].userData.mvSubpnl[i]) {
                    switch (selidx) {
                        case 0:
                            this.showPlaceGlobal(true, false); break;
                        case 1:
                            this.showPlaceBasic(true, false); break;
                        case 2:
                            this.showPlaceBuild(true, false); break;
                        case 3:
                            this.showPlaceMachine(true, false); break;
                        default:
                            this.showPlaceGlobal(true, false);
                    }
                }
                //
                if (this.mvPnl[1].userData.mvSubpnl[i]) {
                    var bShow = (selidx == i);
                    this.mvPnl[1].userData.mvSubpnl[i].setVisible(bShow);
                    if (bShow) {
                        this.mvPnl[1].userData.mvSubpnlIdx = selidx;
                    }
                }
            }
        }

        showPlaceGlobal(bShow, bReCreate) {
            var pnl = this.mvPnl[1];
            if (!pnl) { return; }
            var lang = gLang.muLang;
            var idx = 0;
            if (pnl.userData.mvSubpnl[idx]) {
                if (bReCreate) {
                    pnl.userData.mvSubpnl[idx].dispose();
                }
                else {
                    // update text
                    pnl.userData.mvSubpnl[idx].setVisible(bShow);
                    return;
                }
            }

            var py = pnl.divSize.height - 2;
            var opt = UIStyle.panel(72, 2, pnl.divSize.width - 74, py);
            var subpnl = new UIPanel("editPlaceGlobal", opt, this.mUiMgr, null, false);
            pnl.add(subpnl);
            subpnl.setVisible(bShow);
            pnl.userData.mvSubpnl[idx] = subpnl;

            var that = this;
            var jsObjs = gRoot.mCfg.mObjGlobal;
            var jsList = gRoot.mCfg.mObjGlobal.global;
            var py = 5;
            var cnt = jsList.length;
            var plaObj = function (e) {
                var name = gFispAppEvent.placeEntityGlobal(e.target.id); that.mUiMgr.findUserDlg('dlgentityproperty').addEntity(name);
            }
            for (var i = 0; i < cnt; i++ , py += 30) {
                var name = jsList[i];
                var opt = UIStyle.texture(10, py, 32, 32);
                var img = new UITexture(name + "img", gRoot.mCfg.mstrDataPath + "source/" + jsObjs[name].icon, opt, this.mUiMgr, plaObj, false);
                subpnl.add(img);
                var opt = UIStyle.text(60, py, jsObjs[name].text[lang], 16);
                var txt = new UIText(name + "txt", opt, this.mUiMgr, false);
                subpnl.add(txt);
                var opt = UIStyle.button(10, py, 180, 25, " ", null, "rgba(0,0,0,0.0)", "1px", "1px");
                var btn = new UIButton(name, opt, this.mUiMgr, plaObj, false);
                subpnl.add(btn);
            }
            return subpnl;
        }

        showPlaceBasic(bShow, bReCreate) {
            var pnl = this.mvPnl[1];
            if (!pnl) { return; }
            var lang = gLang.muLang;
            var idx = 1;
            if (pnl.userData.mvSubpnl[idx]) {
                if (bReCreate) {
                    pnl.userData.mvSubpnl[idx].dispose();
                }
                else {
                    // update text
                    pnl.userData.mvSubpnl[idx].setVisible(bShow);
                    return;
                }
            }

            var py = pnl.divSize.height - 5;
            var opt = UIStyle.panel(72, 2, pnl.divSize.width - 74, py);
            var subpnl = new UIPanel("editPlaceBasic", opt, this.mUiMgr, null, false);
            pnl.add(subpnl);
            subpnl.setVisible(bShow);
            pnl.userData.mvSubpnl[idx] = subpnl;

            var that = this;
            var jsObjs = gRoot.mCfg.mObjBasic;
            var jsList = gRoot.mCfg.mObjBasic.basic;
            var py = 5;
            var cnt = jsList.length;
            var plaObj = function (e) {
                var name = gFispAppEvent.placeEntityBasic(e.target.id); that.mUiMgr.findUserDlg('dlgentityproperty').addEntity(name);
            }
            for (var i = 0; i < cnt; i++ , py += 30) {
                var name = jsList[i];
                var opt = UIStyle.texture(10, py, 32, 32);
                var img = new UITexture(name + "img", gRoot.mCfg.mstrDataPath + "source/" + jsObjs[name].icon, opt, this.mUiMgr, plaObj, false);
                subpnl.add(img);
                var opt = UIStyle.text(60, py, jsObjs[name].text[lang], 16);
                var txt = new UIText(name + "txt", opt, this.mUiMgr, false);
                subpnl.add(txt);
                var opt = UIStyle.button(10, py, 180, 25, " ", null, "rgba(0,0,0,0.0)", "1px", "1px");
                var btn = new UIButton(name, opt, this.mUiMgr, plaObj, false);
                subpnl.add(btn);
            }
            return subpnl;
        }

        showPlaceBuild(bShow, bReCreate) {
            var pnl = this.mvPnl[1];
            if (!pnl) { return; }
            var lang = gLang.muLang;
            var idx = 2;
            if (pnl.userData.mvSubpnl[idx]) {
                if (bReCreate) {
                    pnl.userData.mvSubpnl[idx].dispose();
                }
                else {
                    // update text
                    pnl.userData.mvSubpnl[idx].setVisible(bShow);
                    return;
                }
            }

            var py = pnl.divSize.height - 5;
            var opt = UIStyle.panel(72, 2, pnl.divSize.width - 74, py);
            var subpnl = new UIPanel("editPlaceBuild", opt, this.mUiMgr, null, false);
            pnl.add(subpnl);
            subpnl.setVisible(bShow);
            pnl.userData.mvSubpnl[idx] = subpnl;

            var that = this;
            var jsObjs = gRoot.mCfg.mObjBuild;
            var jsList = gRoot.mCfg.mObjBuild.building;
            var py = 5;
            var cnt = jsList.length;
            var plaObj = function (e) {
                var name = gFispAppEvent.placeEntityBuild(e.target.id); that.mUiMgr.findUserDlg('dlgentityproperty').addEntity(name);
            }
            for (var i = 0; i < cnt; i++ , py += 30) {
                var name = jsList[i];
                var opt = UIStyle.texture(10, py, 32, 32);
                var img = new UITexture(name + "img", gRoot.mCfg.mstrDataPath + "source/" + jsObjs[name].icon, opt, this.mUiMgr, plaObj, false);
                subpnl.add(img);
                var opt = UIStyle.text(60, py, jsObjs[name].text[lang], 16);
                var txt = new UIText(name + "txt", opt, this.mUiMgr, false);
                subpnl.add(txt);
                var opt = UIStyle.button(10, py, 180, 25, " ", null, "rgba(0,0,0,0.0)", "1px", "1px");
                var btn = new UIButton(name, opt, this.mUiMgr, plaObj, false);
                subpnl.add(btn);
            }
            return subpnl;
        }

        showPlaceMachine(bShow, bReCreate) {
            var pnl = this.mvPnl[1];
            if (!pnl) { return; }
            var lang = gLang.muLang;
            var idx = 3;
            if (pnl.userData.mvSubpnl[idx]) {
                if (bReCreate) {
                    pnl.userData.mvSubpnl[idx].dispose();
                }
                else {
                    // update text
                    pnl.userData.mvSubpnl[idx].setVisible(bShow);
                    return;
                }
            }

            var py = pnl.divSize.height - 5;
            var opt = UIStyle.panel(72, 2, pnl.divSize.width - 74, py);
            var subpnl = new UIPanel("editPlaceMachine", opt, this.mUiMgr, null, false);
            pnl.add(subpnl);
            subpnl.setVisible(bShow);
            pnl.userData.mvSubpnl[idx] = subpnl;

            var that = this;
            var jsObjs = gRoot.mCfg.mObjMachine;
            var jsList = gRoot.mCfg.mObjMachine.machine;
            var py = 5;
            var cnt = jsList.length;
            var plaObj = function (e) {
                var name = gFispAppEvent.placeEntityMachine(e.target.id); that.mUiMgr.findUserDlg('dlgentityproperty').addEntity(name);
            }
            for (var i = 0; i < cnt; i++ , py += 30) {
                var name = jsList[i];
                var opt = UIStyle.texture(10, py, 32, 32);
                var img = new UITexture(name + "img", gRoot.mCfg.mstrDataPath + "source/" + jsObjs[name].icon, opt, this.mUiMgr, plaObj, false);
                subpnl.add(img);
                var opt = UIStyle.text(60, py, jsObjs[name].text[lang], 16);
                var txt = new UIText(name + "txt", opt, this.mUiMgr, false);
                subpnl.add(txt);
                var opt = UIStyle.button(10, py, 180, 25, " ", null, "rgba(0,0,0,0.0)", "1px", "1px");
                var btn = new UIButton(name, opt, this.mUiMgr, plaObj, false);
                subpnl.add(btn);
            }
            return subpnl;
        }

        showTerrPnl() {
            var idx = 2;
            var lang = gLang.muLang;

            var py = this.mdlg.windowSize.height - 90;
            var opt = UIStyle.panel(2, 50, 296, py);
            var pnl = new UIPanel("editterrpnl", opt, this.mUiMgr, null, false);
            this.mdlg.add(pnl);
            pnl.setVisible(true);

            //var py = pnl.divSize.height - 105;
            //var opt = { x: 5, y: py, w: 170, h: 20, size: 30, value: App.appLang.mNewScene[lang], color: "rgba(1,1,0,1)" };
            //var txtscename = new EngineGUI.GUITextfield("editscename", opt, thisptr.mguimgr, null, false);
            //pnl.add(txtscename);
            //var opt = { x: 185, y: py, w: 100, h: 30, value: App.appLang.mNewScene[lang] };
            //var fun = function () { alert(txtscename.getValue()); };
            //var btn = new EngineGUI.GUIButton("editscenew", opt, thisptr.mguimgr, fun, false);
            //pnl.add(btn);

            //
            if (this.mvPnl && this.mvPnl.length > idx) {
                this.mvPnl[idx] = pnl;
            }
            return pnl;
        }

        showFoliPnl() {
            var idx = 3;
            var lang = gLang.muLang;

            var py = this.mdlg.windowSize.height - 90;
            var opt = UIStyle.panel(2, 50, 296, py);
            var pnl = new UIPanel("editfolpnl", opt, this.mUiMgr, null, false);
            this.mdlg.add(pnl);
            pnl.setVisible(true);

            //
            if (this.mvPnl && this.mvPnl.length > idx) {
                this.mvPnl[idx] = pnl;
            }
            return pnl;
        }

        exchangeUILang(lang: number) {
            this.mdlg.titleWnd(gLang.mSceneOp[lang]);
            this.mdlg.updateText('editSceneName', gLang.mScene[lang]);
            this.mdlg.updateText('editsce', gLang.moptScene[lang]);
            this.mdlg.updateText('editpla', gLang.moptPlace[lang]);
            this.mdlg.updateText('editterr', gLang.moptTerrain[lang]);
            this.mdlg.updateText('editfol', gLang.moptFoliage[lang]);
            //
            this.mdlg.updateText('editscenew', gLang.mNewScene[lang]);
            this.mdlg.updateText('txtsceneopgroup', gLang.mMultiuser[lang]);
            this.mdlg.updateText('txtsceneoppub', gLang.mPublishScene[lang]);
            this.mdlg.updateText('editsceexport', gLang.mJoin[lang]);
            this.mdlg.updateText('editsceupdate', gLang.mUpdate[lang]);
            this.mdlg.updateText('editscesave', gLang.mSave[lang]);
            this.mdlg.updateText('editscedel', gLang.mDelete[lang]);
            //
            this.mdlg.updateText('editplaglobal', gLang.mGlobal[lang]);
            this.mdlg.updateText('editplabasic', gLang.mBasic[lang]);
            this.mdlg.updateText('editplabuild', gLang.mBuild[lang]);
            this.mdlg.updateText('editplamachine', gLang.mMachine[lang]);
            //
            var pnl = this.mvPnl[1];
            var idx = 0;
            if (pnl && pnl.userData.mvSubpnl[idx]) {
                var jsObjs = gRoot.mCfg.mObjGlobal;
                var jsList = gRoot.mCfg.mObjGlobal.global;
                var cnt = jsList.length;
                for (var i = 0; i < cnt; i++) {
                    var name = jsList[i];
                    this.mdlg.updateText(name + "txt", jsObjs[name].text[lang]);
                }
            }
            var idx = 1;
            if (pnl && pnl.userData.mvSubpnl[idx]) {
                var jsObjs = gRoot.mCfg.mObjBasic;
                var jsList = gRoot.mCfg.mObjBasic.basic;
                var cnt = jsList.length;
                for (var i = 0; i < cnt; i++) {
                    var name = jsList[i];
                    this.mdlg.updateText(name + "txt", jsObjs[name].text[lang]);
                }
            }
            var idx = 2;
            if (pnl && pnl.userData.mvSubpnl[idx]) {
                var jsObjs = gRoot.mCfg.mObjBuild;
                var jsList = gRoot.mCfg.mObjBuild.building;
                var cnt = jsList.length;
                for (var i = 0; i < cnt; i++) {
                    var name = jsList[i];
                    this.mdlg.updateText(name + "txt", jsObjs[name].text[lang]);
                }
            }
            var idx = 3;
            if (pnl && pnl.userData.mvSubpnl[idx]) {
                var jsObjs = gRoot.mCfg.mObjMachine;
                var jsList = gRoot.mCfg.mObjMachine.machine;
                var cnt = jsList.length;
                for (var i = 0; i < cnt; i++) {
                    var name = jsList[i];
                    this.mdlg.updateText(name + "txt", jsObjs[name].text[lang]);
                }
            }
        }

        newScene(idx: number, strName: string) {
            if (idx < 0 || !strName || strName.length <= 0)
                return;
            var strTemp = strName;
            var pnl = this.mvPnl[0];
            if (Fisp.Utility.strLength(strTemp) > 6) {
                strTemp = strTemp.substr(0, 6) + "...";
            }
            var yOff = 5;
            var col = 4;
            var i = Math.floor(idx / col);
            var j = idx - col * i;
            var sx = j * (64 + 6);
            var sy = i * (64 + 6) + yOff;
            var opt = UIStyle.text(sx, sy + 45, strTemp, 16);
            var txt = new UIText(strName + '_scenetxt', opt, this.mUiMgr, false);
            pnl.add(txt);
            var that = this;
            var clickImg = function (e) { that.selectSceneByImgTag(e.target); };
            var img = new UITexture(strName + '_sceneimg', gRoot.mCfg.mstrDataPath + "source/leaf.png", { w: 64, h: 64, x: j * (64 + 6), y: i * (64 + 6) + yOff }, this.mUiMgr, clickImg, false);
            pnl.add(img);
            var opt = UIStyle.button(j * (64 + 6), i * (64 + 6) + yOff, 64, 64, " ", null, "rgba(0,0,0,0.0)", "1px", "1px");
            var btn = new UIButton(strName + '_scenebtn', opt, this.mUiMgr, clickImg, false);
            pnl.add(btn);
            // set as current
            gUser.selectScene(idx);
            this.selectSceneByIdx(idx);
        }

        updateSceneItem(idx: number, strName: string) {
            var cnt = gUser.sceneCnt();
            for (var i = 0; i < cnt; i++) {
                this.newScene(i, gUser.sceneName(i));
            }
            var idx = (gUser.sceneCnt() > 0) ? 0 : -1;
            this.selectSceneByIdx(idx);
        }

        delAllSceneItem() {
            var pnl = this.mvPnl[0];
            var strName = "";
            var cnt = gUser.sceneCnt();
            for (var i = 0; i < cnt; i++) {
                strName = gUser.sceneName(i);
                this.mdlg.del(strName + '_scenetxt');
                this.mdlg.del(strName + '_sceneimg');
                this.mdlg.del(strName + '_scenebtn');
            }
        }
    }

    //
    export class DlgEntityProperty extends IWnd {
        mUiMgr: UIMgr;

        constructor() {
            super('dlgentityproperty');
        }

        addEntity(strName) {
        }
    }

}