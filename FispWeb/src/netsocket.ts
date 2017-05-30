namespace Fisp {
    export class NetSocket {
        mwsSvr: string = "";
        msocket: WebSocket = null;
        mstrID: string = "";
        mvMsg: Array<any> = [];
        mstrUser: string = "";

        constructor() {
            this.mwsSvr = "";
            this.msocket = null;
            this.mstrID = "";
            this.mvMsg = [];
            this.mstrUser = "";
        }

        connect(wsSvr: string) {
            if (this.msocket != null && this.msocket.readyState == 1 && wsSvr == this.mwsSvr) {
                return true;
            }
            if (!wsSvr || wsSvr.length <= 0) {
                alert("Connect parameter error!\n");
                return false;
            }
            try {
                this.msocket = new WebSocket(wsSvr);
                this.mwsSvr = wsSvr;
            }
            catch (e) {
                alert("Failed to connect to server!\n" + e.message);
                return false;
            }

            var that = this;
            this.msocket.onopen = function (evt) {
                //that.msocket.send('0visitor');
                //that.msocket.send('3subscribe');
            }

            this.msocket.onmessage = function (msg) {
                var arg1 = "";
                var arg2 = "";
                var str = msg.data;
                var flag = str.indexOf(":");
                if (flag != -1) {
                    arg1 = str.substr(0, flag);
                    arg2 = str.substr(flag + 1);
                }
                else {
                    arg1 = str;
                }
                Fisp.gRoot.mFrame.onReceMsg(arg1, arg2);
            }

            this.msocket.onerror = function (evt) {
                //gMsgbox.showMsg("Connect error: " + evt.message);
            }

            this.msocket.onclose = function (evt) {
                //App.appUser.signOut();
            }
            return true;
        }

        sendMsg(strMsg, eType, strUser) {
            if (!strMsg || strMsg == "") {
                return false;
            }
            if (!this.msocket || this.msocket.readyState != 1) {
                this.connect(this.mwsSvr);
                gMsgbox.showMsg(gLang.mCSErr[gLang.muLang]);
                return;
            }
            //
            eType = eType || "1";
            strUser = strUser ? (":" + strUser) : "";
            var bSend = false;
            try {
                //this.msocket.send(eType + strMsg + strUser);
                this.msocket.send(strMsg + strUser);
                bSend = true;
            }
            catch (e) {
                bSend = false;
                this.errlog(e);
            }
            return bSend;
        }

        sendGroupMsg(strMsg) {
            if (strMsg == "" || this.msocket == null || this.msocket.readyState != 1) {
                return false;
            }
            var bSend = false;
            try {
                this.msocket.send('3publish|' + strMsg);
                bSend = true;
            }
            catch (e) {
                bSend = false;
                this.errlog(e);
            }
            return bSend;
        }

        sendStreamMsg(strMsg, strFile, strUser) {
            if (strMsg == "" || this.msocket == null || this.msocket.readyState != 1) {
                return false;
            }
            var bSend = true;
            strFile = strFile || "";
            try {
                this.msocket.send("1stream,start:" + strFile + ":" + strUser);
                alert("1stream,start:" + strFile + ":" + strUser);
            }
            catch (e) {
                bSend = false;
                this.errlog(e);
                return false;
            }
            var uCnt = Math.ceil(strMsg.length / 1024);
            alert(strMsg.length / 1024 + "," + uCnt);
            var strSub;
            for (var i = 0; i < uCnt; i++) {
                strSub = (i + 1 == uCnt) ? strMsg.substr(i * 1024) : strMsg.substr(i * 1024, 1024);
                try {
                    this.msocket.send("1stream:" + strSub);
                }
                catch (e) {
                    bSend = false;
                    this.errlog(e);
                    return false;
                }
            }
            //
            try {
                this.msocket.send("1stream,end:" + strFile + ":" + strUser);
            }
            catch (e) {
                bSend = false;
                this.errlog(e);
                return false;
            }
            return bSend;
        }

        close = function () {
            this.msocket.close();
        }

        state = function () {
            var wss = (this.msocket) ? this.msocket.readyState : 3;
            return wss;
        }

        isConnected = function () {
            return (null != this.msocket && this.msocket.readyState == 1);
        }

        errlog = function (e) {
            gMsgbox.showMsg("ERROR: " + e.name + "\n");
            //gMsgbox.showMsg("num: " + e.number + "\n" + "name: " + e.name + "\n" + "des: " + e.description + "\n" + "msg: " + e.message + "\n");
        }

        proceMsg = function (type, msg) {
            //var vstr = msg.split(":");

            //if (vstr[0] == "signin" && vstr.length > 1 && vstr[1].length > 0) {
            //    App.appUser.mstrName = vstr[1];
            //    App.appUi.wseUI(App.appLang.muLang, App.appUser.mstrName, true);
            //}
            //else if (vstr[0] == "signup") {
            //    alert(vstr[1]);
            //}
            //else if (vstr[0] == "signout") {
            //    App.appUser.mstrName = "";
            //    App.appUi.wseUI(App.appLang.muLang, App.appUser.mstrName, true);
            //}
            //else if (vstr[0] == "error") {
            //    alert(vstr[1]);
            //}

            //    if (vstr[0] == "kindlist") {
            //        Fisp.mcUi.setKindList(vstr[1]);
            //    }
            //    else if (vstr[0] == "scenelist") {
            //        App.appLgc.mstrSceneList = vstr[1];
            //        Fisp.mcUi.setSceneList(vstr[1]);
            //        //
            //        if (!Fisp.mcUi.mbGetScenelist) {
            //            Fisp.mcRender.loadDefScene();
            //        }
            //        Fisp.mcUi.mbGetScenelist = true;
            //    }
            //    else if (vstr[0] == "geolist,3") {
            //        App.appLgc.setGeoList(3, vstr[1]);
            //        //alert(vstr[1]);
            //    }
            //    else if (vstr[0] == "geolist,4") {
            //        App.appLgc.setGeoList(4, vstr[1]);
            //    }
            //    else if (vstr[0] == "geolist,5") {
            //        //App.appLgc.setGeoList(5, vstr[1]);
            //    }
            //    else if (vstr[0] == "check") {
            //    }
            //    else if (vstr[0] == "signin") {
            //        document.getElementById("login_name").style.display = "none";
            //        document.getElementById("login_pswd").style.display = "none";
            //        document.getElementById("h1").textContent = vstr[1];
            //        document.getElementById("submit_signin").value = App.appLang.mSignout[App.appLang.muLang];
            //        document.getElementById("submit_signup").value = App.appLang.mEditScene[App.appLang.muLang];
            //        App.appUser.mbSignin = true;
            //        App.appUser.mstrName = vstr[1];
            //        //
            //        App.appUser.ExitEdit();
            //    }
            //    else if (vstr[0] == "signup") {
            //        alert(vstr[1]);
            //        document.getElementById("login_name").value = "";
            //        document.getElementById("login_pswd").value = "";
            //        window.open('../index.html', "_blank");
            //    }
            //    else if (vstr[0] == "newscene") {
            //        var list = document.getElementById("scenelist");
            //        var node = document.createElement("option");
            //        node.value = vstr[1];
            //        node.text = vstr[1];
            //        list.appendChild(node);
            //        list.selectedIndex = list.options.length - 1;
            //        //
            //        document.getElementById("btNewScene").disabled = false;
            //    }
            //    else if (vstr[0] == "loadlight") {
            //        App.appLgc.loadLit(vstr[1]);
            //    }
            //    else if (vstr[0] == "loadobject") {
            //        App.appLgc.loadObj(vstr[1]);
            //    }
            //    else if (vstr[0] == "stream") {
            //        document.getElementById('btiMesh').disabled = false;
            //        document.getElementById('upmesh').disabled = false;
            //        document.getElementById('upprog').style.display = "none";
            //    }
            //    else if (vstr[0] == "error") {
            //        alert(vstr[1]);
            //        if (vstr[2] && vstr[2] == "newscene") {
            //            document.getElementById("btNewScene").disabled = false;
            //        }
            //    }
        }

        onMsg(type, arg1, arg2) {
            //alert(type + ": " + arg1 + ", " + arg2);
            if (type == "1") {
                this.proceMsg(type, arg1);
            }
            else if (type == "3") {
                //    var strID = arg1;
                //    document.getElementById("chatmsg").value += strID + ":\n" + arg2 + "\n\n";
                //    document.getElementById("chatmsg").scrollTop = document.getElementById("chatmsg").scrollHeight;
                //    if (strID != mstrID && Fisp.mcUi.meMainDlgOpt != 4) {
                //        document.getElementById("optChat").value = App.appLang.moptChat[App.appLang.muLang] + " *";
                //    }
            }
        }
    }
    
}