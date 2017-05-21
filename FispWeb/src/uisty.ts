namespace Fisp {
    export class UIStyle {

        constructor() {
        }

        static window(x, y, w, h, txtTitle, clrTitle?, bkColor?, bkImg?, zIndex?): any {
            var opt: any;
            opt = new Object();
            opt.x = x;
            opt.y = y;
            opt.w = w;
            opt.h = h;
            opt.backgroundColor = bkColor || "rgba(40, 40, 40, 0.6)";
            opt.backgroundImage = bkImg || null;
            opt.titleColor = clrTitle || "rgba(255, 255, 255, 1.0)";
            opt.closeButton = "false";
            opt.textTitle = txtTitle || "Window";
            opt.borderWindow = "2px solid black";
            opt.colorContent = "rgba(0.5, 0.5, 0.5, 0.1)";
            opt.zIndex = zIndex || 0;
            return opt;
        }

        static panel(x, y, w, h, bkColor?, border?, borderRadius?): any {
            var opt: any;
            opt = new Object();
            opt.x = x;
            opt.y = y;
            opt.w = w;
            opt.h = h;
            opt.backgroundColor = bkColor || "rgba(0, 0, 0, 0.5)";
            opt.borderPanel = border || "0px solid black";
            opt.borderRadiusPanel = borderRadius || "10px";
            return opt;
        }

        static button(x, y, w, h, val, bkImage?, color?, bkColor?, border?, borderRaduis?): any {
            var opt: any;
            opt = new Object();
            opt.x = x;
            opt.y = y;
            opt.w = w || 50;
            opt.h = h || 20;
            opt.value = val || "";
            opt.backgroundImage = bkImage || null;
            opt.colorText = color || "rgba(0, 0, 0, 1.0)";
            opt.backgroundColor = bkColor || "rgba(196, 196, 196, 1.0)";
            opt.borderButton = border || "1px solid black";
            opt.borderRadiusButton = borderRaduis || "8px";
            return opt;
        }

        static option(x, y, w, h, val, color?, bkColor?, border?, borderRaduis?): any {
            var opt: any;
            opt = new Object();
            opt.x = x;
            opt.y = y;
            opt.w = w || 50;
            opt.h = h || 20;
            opt.value = val || "";
            opt.colorText = color || "rgba(0, 0, 0, 1.0)";
            opt.backgroundColor = bkColor || "rgba(200, 200, 200, 1.0)";
            opt.borderButton = border || "1px solid black";
            opt.borderRadiusButton = borderRaduis || "1px";
            return opt;
        }

        static text(x, y, txt, size?, color?): any {
            var opt: any;
            opt = new Object();
            opt.x = x;
            opt.y = y;
            opt.text = txt;
            opt.color = color || "rgba(240, 240, 240, 1.0)";
            opt.size = size || 30;
            return opt;
        }

        static edit(x, y, w, h, val, type?, color?, bkColor?, borderColor?): any {
            var opt: any;
            opt = new Object();
            opt.x = x;
            opt.y = y;
            opt.w = w;
            opt.h = h;
            opt.value = val;
            opt.type = type || "text";
            opt.color = color || "rgba(255, 255, 255, 1.0)";
            opt.background = bkColor || "rgba(64, 64, 64, 0.5)";
            opt.border = "1px solid black";
            return opt;
        }

        static editArea(x, y, row, col, val, size?, readOnly?, color?, bkColor?, borderColor?): any {
            var opt: any;
            opt = new Object();
            opt.x = x;
            opt.y = y;
            opt.row = row;
            opt.col = col;
            opt.value = val;
            opt.size = size || 24;
            //opt.type = type || "text";
            opt.readOnly = readOnly || false;
            opt.color = color || "rgba(255, 255, 255, 1.0)";
            opt.background = bkColor || "rgba(64, 64, 64, 0.5)";
            opt.border = "1px solid black";
            return opt;
        }

        static select(x, y, w, h): any {
            var opt: any;
            opt = new Object();
            opt.x = x;
            opt.y = y;
            opt.w = w;
            opt.h = h;
            //opt.value = val;
            //opt.color = color || "rgba(0, 0, 0, 1.0)";
            //opt.background = bkColor || "rgba(200, 200, 200, 1.0)";
            return opt;
        }

        static checkbox(x, y, size = 1): any {
            var opt: any;
            opt = new Object();
            opt.x = x;
            opt.y = y;
            opt.size = size;
            return opt;
        }

        static texture(x, y, w, h): any {
            var opt: any;
            opt = new Object();
            opt.x = x;
            opt.y = y;
            opt.w = w;
            opt.h = h;
            return opt;
        }

    }

    //
    export class IWnd {
        mstrWndName: string;

        constructor(name: string) {
            this.mstrWndName = name || '';
        }

        name() {
            return this.mstrWndName;
        }
    }


    //
    export class Lang {
        muLang: number;
        //
        mlang = ["中文", "English"];
        mfpsmean = ["fps", "帧/秒"];
        mOffline = ["Offline", "离线"];
        mCSconi = ["Connecting ...", "正在连接"];
        mCScon = ["Connected", "已连接"];
        mCScloi = ["Closing ...", "正在关闭"];
        mCSclo = ["Closed", "已关闭"];
        //
        mMsgTitle = ['', ''];//["DIYW3D can edit and publish 3D scene online", "DIYW3D可在线编辑、发布三维场景"];
        //mMsgHelp = ["Welcome to DIYW3D.<br>" + this.mMsgTitle[0] + ".<br>Have any question, please feel free contact us:<br>diyw3d@gmail.com .<br>Thank you!", "欢迎光临 DIYW3D。<br>" + this.mMsgTitle[1] + "。<br>有任何问题请垂询:<br>diyw3d@gmail.com 。<br>谢谢!"];
        mMsgHelp = ['fisper@163.com', 'fisper@163.com'];
        mHelp = ["Help", "帮助"];
        mainTitle = ["DIYW3D can edit and publish 3D scene online", "DIYW3D可在线编辑、发布三维场景"];
        mmainMenu = ["Main Dialog", "主对话框"];
        mSignRegs = ["Signin | Signup", "登录 | 注册"];
        minName = ["Account", "帐号"];
        minPswd = ["Password", "密码"];
        mSignin = ["Signin", "登录"];
        mSignout = ["Signout", "退出"];
        mSignup = ["Signup", "注册"];
        mWelcome = ["Welcome", "欢迎"];
        mUserinfo = ["User info", "个人信息"];
        mSceneCnt = ["Scene Count", "场景总数"];
        mPublished = ["Published", "发布场景"];
        //
        mPlay = ["Play", "播放"];
        mFullscreen = ["Fullscreen", "全屏模式"];
        mWindowMode = ["Windowed", "窗口模式"];
        mShowEditor = ["Show Editor", "显示编辑器"];
        mHideEditor = ["Hide Editor", "隐藏编辑器"];
        mRunVR = ["Start VR (download exe)", "启动 VR (下载 exe程序)"];
        mRunMR = ["Start Holographic (download app)", "启动 Holographic (下载 app程序)"];
        mBrowseScene = ["Browse Scene", "浏览场景"];
        //mSettingMgr = ["Setting", "设置属性"];
        mPlayScene = ["Play Scene", "播放场景"];
        mEditScene = ["Edit Scene", "编辑场景"];
        mExitEdit = ["Exit Edit", "退出编辑"];
        //
        mReturn = ["Return", "返回"];
        mClose = ["Close", "关闭"];
        mAbout = ["About", "关于"];
        mMsgWnd = ["Msg Dialog", "信息框"];
        //
        mSceneOp = ["Edit Dialog", "编辑对话框"];
        mPropertyOp = ["Property Dialog", "属性对话框"];
        mScene = ["Scene", "场景"];
        mGlobal = ["Global", "全局"];
        mBasic = ["Basic", "基本"];
        mBuild = ["Building", "建筑"];
        mMachine = ["Machine", "机械"];
        moptScene = ["Scene", "场景"];
        moptPlace = ["Place", "放置"];
        moptTerrain = ["Terrain", "地形"];
        moptFoliage = ["Foliage", "植被"];
        mNewScene = ["New Scene", "新建场景"];
        mMultiuser = ["Teamwork", "多人协作"];
        mPublishScene = ["Public", "公开"];
        mJoin = ["Invite", "邀请"];//["Join", "加入"];
        mUpdate = ["Update", "更新"];
        mSave = ["Save", "保存"];
        mDelete = ["Delete", "删除"];

        mString = {
            dlgMain: {
                title: ["Main Dialog", "主对话框"],
                chat: ["Chat", "聊天"]
            },
            dlgSignup: {
                title: ["Signup Dialog", "注册对话框"],
                repeadpw: ["Repead", "重复密码"],
                email: ["E-Mail", "电子邮箱"]
            },
            dlgChat: {
                title: ["Chat Dialog", "聊天对话框"],
                send: ["Send", "发送"]
            },
            dlgSetting: {
                title: ["Setting Dialog", "属性设置对话框"], ui: ["UI", "界面"], render: ["Render", "渲染"], Music: ["Music", "音乐"], other: ["Other", "其它"],
                hideDlgScene: ["Hide Scene Edit Dialog", ""]
            },
            dlgIMRes: {
                title: ["IM Dialog", "即时通对话框"], msg: ["Msg", "信息"]
            },
            msg: {
                nameempty: ["Name can not be empty!", "名字不能为空！"],
                nameexist: ["Name already exists!", "名字已经存在！"],
                welcome: ["Welcome", "欢迎"],
                canotempty: ["Account or password can not be empty!", "账号或密码不能为空！"],
                signupPWMismatch: ["The passwords not match!", "两次密码不匹配"],
                signupok: ["Signup OK!", "注册成功！"],
                sceneAtMax: ["Scene count is already at the maximum!", "场景已达最大值！"],
                chatEmpty: ["MSG can not be empty!", "消息不能为空！"]
            },
            others: {
                visitor: ["Visitor", "游客"]
            }
        };

        constructor() {
            this.muLang = 0;
        }

        shift() {
            this.muLang++;
            if (this.muLang >= this.mlang.length) {
                this.muLang = 0;
            }
            return this.muLang;
        }
    }

    export var gLang: Lang = new Fisp.Lang();

    //
    export class Msgbox extends IWnd {
        mUiMgr: UIMgr;
        mdlg: UIWindow;

        constructor(uiMgr: UIMgr) {
            super('dlginfo');
            this.mUiMgr = uiMgr;
            this.build();
        }

        build() {
            var lang = gLang.muLang;
            var cvsSize = this.mUiMgr.getCanvasSize();
            var cx = 400;
            var cy = 300;
            var x = (0.5 * (cvsSize.width - cx)); var y = (0.5 * (cvsSize.height - cy));
            var opt = UIStyle.window(x, y, cx, cy, gLang.mMsgWnd[lang], null, "rgba(40, 40, 40, 0.9)", null, 10);
            this.mdlg = new UIWindow(this.mstrWndName, opt, this.mUiMgr);
            var opt = UIStyle.text(0, 34, "", 24, "rgba(240,240,14,1.0)");
            var txt = new UIText("msg", opt, this.mUiMgr, false);
            this.mdlg.add(txt);
            this.mdlg.userData.mtxtMsg = txt;
            var opt = UIStyle.button(370, 0, 30, 30, "X", null, "white", "rgba(200,4,4,1.0)");
            var that = this;
            var fun = function (e) { that.mdlg.setVisible(false, false); that.mdlg.userData.mtxtMsg.updateText(" "); if (that.mdlg.userData.mdlgReturn) { (<UIWindow>that.mdlg.userData.mdlgReturn).setVisible(true); } };
            var btn = new UIButton("dlginfoclose", opt, this.mUiMgr, fun, false);
            this.mdlg.add(btn);
            this.mdlg.setVisible(false, false);
            this.mdlg.userData.mdlgReturn = false;
        }

        showMsg(msg, dlgReturn = null) {
            if (!msg || msg.length <= 0) { return; }
            if (dlgReturn)
                (<UIWindow>dlgReturn).setVisible(false);
            this.mdlg.userData.mtxtMsg.updateText(msg);
            this.mdlg.setVisible(true, false);
            this.mdlg.userData.mdlgReturn = dlgReturn;
        }

        exchangeUILang(lang: number) {
            this.mdlg.titleWnd().innerHTML = gLang.mMsgWnd[lang];
        }
    }
    export var gMsgbox: Msgbox = null;

    //
    export class DlgSys extends IWnd {
        mUiMgr: UIMgr;
        mmainBtn: UIButton;
        mtexLogo: UITexture;
        mTextFPS: UIText;
        mTextWSS: UIText;
        //mdlgMain: DlgMain;

        constructor(uiMgr) {
            super('dlgsys');
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
            var cvsSize = this.mUiMgr.getCanvasSize();
            //var that = this;
            //var clickLogo = function () {
            //    var bShow = (that.mdlgMain) ? (!that.mdlgMain.isVisible()) : false;
            //    that.mdlgMain.show(bShow);
            //};
            ////this.mtexLogo = new UITexture("logo", "data/source/logo.png", { w: 64, h: 64, x: (cvsSize.width / 2 - 32), y: (cvsSize.height - 64) }, this.mUiMgr, clickLogo, true);
            //var opt = UIStyle.button((cvsSize.width / 2 - 32), (cvsSize.height - 64), 64, 64, "", "data/source/logo.png", "white", "black", "0px");
            //this.mmainBtn = new UIButton("mainmenu", opt, this.mUiMgr, clickLogo, true);

            var opt = UIStyle.text(2, 0, '', 20);
            this.mTextFPS = new UIText('fps', opt, this.mUiMgr, true);
            var opt = UIStyle.text(2, 20, '', 20);
            this.mTextWSS = new UIText('wss', opt, this.mUiMgr, true);
        }

        resize(evt) {
            //if (null != this.mmainBtn) {
            //    var cvsSize = this.mUiMgr.getCanvasSize();
            //    this.mmainBtn.resize((cvsSize.width / 2 - 32), (cvsSize.height - 64), 64, 64);
            //}
        }

        exchangeUILang(lang: number) {
            //this.mmainBtn.value = gLang.mmainMenu[lang];
            //this.mTextFPS = ;
            //this.mTextWSS = ;
        }

    }
    export var gDlgSys: DlgSys = null;

}