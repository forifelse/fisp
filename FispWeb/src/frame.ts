namespace Fisp {
    export class Frame {
        doSetup: Function = null;
        doCreate: Function = null;
        doBuildScene: Function = null;
        doBuildUi: Function = null;
        doUpdate: Function = null;
        doPicked: Function = null;
        doResize: Function = null;
        doDestroy: Function = null;
        doReceMsg: Function = null;
        doKeyDown: Function = null;
        doKeyUp: Function = null;
        doMouseDown: Function = null;
        doMouseMove: Function = null;
        doMouseUp: Function = null;
        doMouseWheel: Function = null;
        doTouchStart: Function = null;
        doTouchMove: Function = null;
        doTouchEnd: Function = null;
        //
        mNet: NetSocket;
        mUiMgr: UIMgr;
        mInput: Input;
        mTimer: number;

        constructor() {
            this.doSetup = null;
            this.doCreate = null;
            this.doBuildScene = null;
            this.doBuildUi = null;
            this.doUpdate = null;
            this.doPicked = null;
            this.doResize = null;
            this.doDestroy = null;
            this.doReceMsg = null;
            this.doKeyDown = null;
            this.doKeyUp = null;
            this.doMouseDown = null;
            this.doMouseMove = null;
            this.doMouseUp = null;
            this.doMouseWheel = null;
            this.doTouchStart = null;
            this.doTouchMove = null;
            this.doTouchEnd = null;

            //
            this.mNet = new NetSocket();
            this.mUiMgr = null;
            this.mInput = new Input();
            this.mInput.addEvent();
            this.mTimer = null;
        }

        setCallback(opt) {
            if (opt.onSetup)
                this.doSetup = opt.onSetup;
            if (opt.onCreate)
                this.doCreate = opt.onCreate;
            if (opt.onBuildScene)
                this.doBuildScene = opt.onBuildScene;
            if (opt.onBuildUi)
                this.doBuildUi = opt.onBuildUi;
            if (opt.onUpdate)
                this.doUpdate = opt.onUpdate;
            if (opt.onPicked)
                this.doPicked = opt.onPicked;
            if (opt.onResize)
                this.doResize = opt.onResize;
            if (opt.onDestroy)
                this.doDestroy = opt.onDestroy;

            if (opt.onReceMsg)
                this.doReceMsg = opt.onReceMsg;

            if (opt.onKeyDown)
                this.doKeyDown = opt.onKeyDown;
            if (opt.onKeyUp)
                this.doKeyUp = opt.onKeyUp;
            if (opt.onMouseDown)
                this.doMouseDown = opt.onMouseDown;
            if (opt.onMouseMove)
                this.doMouseMove = opt.onMouseMove;
            if (opt.onMouseUp)
                this.doMouseUp = opt.onMouseUp;
            if (opt.onMouseWheel)
                this.doMouseWheel = opt.onMouseWheel;
            if (opt.onTouchStart)
                this.doTouchStart = opt.onTouchStart;
            if (opt.onTouchMove)
                this.doTouchMove = opt.onTouchMove;
            if (opt.onTouchEnd)
                this.doTouchEnd = opt.onTouchEnd;
        }

        onSetup() {
            this.mNet.connect('ws://argbm.ticp.net:10545');
            //this.mNet.connect('ws://fre3d.oicp.net:37185');
            //this.mNet.connect('ws://localhost:81');
            //this.setTimer();
        }

        onCreate() {
        }

        onBuildScene() {
            if (null != this.doBuildScene)
                this.doBuildScene();
        }

        onBuildUi(cvs) {
            var css = "button {cursor:pointer;}";
            var options = { themeRoot: "./css/", themeGUI: "default" };
            this.mUiMgr = new Fisp.UIMgr(cvs, css, options);
            gMsgbox = new Msgbox(this.mUiMgr, 68, 2);
            gDlgSys = new DlgSys(this.mUiMgr, 2, 0);
            this.mUiMgr.regUserDlg(gMsgbox);
            this.mUiMgr.regUserDlg(gDlgSys);
            if (null != this.doBuildUi)
                this.doBuildUi(this.mUiMgr);
        }

        onUpdate(delta: number) {
            this.timerWorker();
        }

        onPicked() {
        }

        onResize(evt) {
            //gRoot.mEngine.mRender.onresize();
            if (this.doResize)
                this.doResize(evt);
        }

        onDestroy() {
            clearTimeout(this.mTimer);
        }

        onReceMsg(arg1, arg2) {
            //var flag = arg2.indexOf(":");
            //var sub1, sub2;
            //if (flag != -1) {
            //    sub1 = arg2.substr(0, flag);
            //    sub2 = arg2.substr(flag + 1);
            //}
            if (arg1 == "onopen") {
                this.mNet.mstrID = arg2;
                gUser.mstrSocketID = arg2;
            }
            else if (arg1 == "onclose") {
            }
            else if (arg1 == "onerror") {
            }
            this.doReceMsg(arg1, arg2, this.mUiMgr);
        }

        onKeyDown() {
        }

        onKeyUp() {
        }

        onMouseDown() {
        }

        onMouseMove() {
        }

        onMouseUp() {
        }

        onMouseWheel() {
        }

        onTouchStart() {
        }

        onTouchMove() {
        }

        onTouchEnd() {
        }

        timerWorker() {
            var fps = gRoot.mEngineImp.fps().toFixed() + " " + gLang.mfpsmean[gLang.muLang];
            gDlgSys.mTextFPS.updateText(fps);
            var wss = this.netState();
            gDlgSys.mTextWSS.updateText(wss);
        }

        setTimer() {
            var inter = 400;
            this.mTimer = setInterval(() => this.timerWorker, inter);
        }

        netState() {
            var str = "";
            var idx = gLang.muLang;
            if (navigator.onLine) {
                var wss = (this.mNet) ? this.mNet.state() : -1;
                switch (wss) {
                    case 0: str = gLang.mCSconi[idx]; break;
                    case 1: str = gUser.mbSignin ? gUser.mstrName : gLang.mCScon[idx]; break;
                    case 2: str = gLang.mCScloi[idx]; break;
                    case 3: str = gLang.mCSclo[idx]; break;
                    default: str = gLang.mCSclo[idx];
                }
            }
            else {
                str = gLang.mOffline[idx];
            }
            return str;
        }

    }


}