namespace Fisp {
    export class FispRoot {
        mCvs: HTMLCanvasElement;
        mFrame: Frame;
        mEngineImp: IEngine;
        //
        mCfg: SysConfig;
        mguimgr: UIMgr = null;

        constructor(optCallback = null) {
            this.mFrame = new Frame();
            this.mCfg = new SysConfig();
            this.setCallback(optCallback);
        }

        setCallback(optCallback) {
            if (optCallback)
                this.mFrame.setCallback(optCallback);
        }

        loadCfg() {
            this.mCfg.loadCfg();
        }

        create() {
            this.mFrame.onSetup();
            ////this.mEngineImp = new Engine();
            this.mEngineImp = new Fisp.RdrImp(this.mCvs);
            this.mEngineImp.create();
            this.mFrame.onCreate();
            this.mFrame.onBuildUi(this.mCvs);
            this.mFrame.onBuildScene();
        }

        renderLoop() {
            var delta = 0.001;
            //this.mEngine.mRender.onRender(delta);
            this.mFrame.onUpdate(delta);
            this.mEngineImp.renderLoop();
        }

        stop() {
            this.mEngineImp.stop();
        }

        static fullscreen(bFull: boolean, ele?) {
            ele = document.getElementById('cvsid') || ele;
            if (bFull) {
                var docElm = document.documentElement;
                var enterFull = docElm.requestFullscreen
                    || docElm.webkitRequestFullscreen
                    || docElm.webkitRequestFullScreen
                    || (<any>docElm).msRequestFullscreen
                    || (<any>docElm).mozRequestFullScreen;
                enterFull.call(docElm);
            }
            else {
                var exitFull = document.exitFullscreen
                    || document.webkitCancelFullScreen
                    || document.webkitExitFullscreen
                    || (<any>document).msExitFullscreen
                    || (<any>document).mozCancelFullScreen;
                exitFull.call(document);
            }
            //ele.stopPropagation();
        }

    }
    //export var gRoot: FispRoot = null;
    export var gRoot: Fisp.FispRoot = new Fisp.FispRoot();

    window.onload = () => {
        Fisp.gRoot.mCvs = <HTMLCanvasElement>document.getElementById('cvsid');
        Fisp.gRoot.loadCfg();
        Fisp.gRoot.create();
        (function renderLoop() {
            requestAnimationFrame(renderLoop);
            Fisp.gRoot.renderLoop();
        })();
    };

    window.close = () => {
        Fisp.gRoot.stop();
    }
    
}