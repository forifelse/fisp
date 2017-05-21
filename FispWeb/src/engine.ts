/// <reference path="uilib.ts" />
namespace Fisp {
    export class Engine{// extends IEngine {
        mTimer: number = null;
        mRender: Render = null;
        mScene: Scene = null;
        mData: NetDatabase = null;

        constructor() {
            //super();
        }

        create() {
            this.mRender = new Render();
            this.mRender.createScene();
            this.mRender.createUI();
        }

        renderLoop() {
            var delta = 0.001;
            this.mRender.onRender(delta);
        }

        timerWorker() {
        }

        setTimer() {
            var inter = 400;
            this.mTimer = setInterval(() => this.timerWorker, inter);
        }

        stop() {
            clearTimeout(this.mTimer);
        }

        resize() {
        }

        fps(): number {
            return 60;
        }



    }

}