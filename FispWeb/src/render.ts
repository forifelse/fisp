namespace Fisp {
    export class Render {
        mCvs: HTMLCanvasElement = null;
        mGL: WebGLRenderingContext = null;
        mProgram: WebGLProgram = null;
        mVS: WebGLShader = null;
        mPS: WebGLShader = null;
        //
        mShader: Shader = null;
        mScene: Scene = null;
        mUiMgr: UIMgr = null;
        //
        mmatView: EngineCore.Matrix = null;
        mmatProj: EngineCore.Matrix = null;
        //mmatView: Float32Array = null;
        //mmatProj: Float32Array = null;

        constructor() {
            this.mCvs = <HTMLCanvasElement>document.getElementById('cvsid');
            var dc: CanvasRenderingContext2D = null;
            try {
                //dc = canvas.getContext("2d");
                //dc.fillStyle = "0x0000ff";
                //dc.fillRect(0, 0, 800, 600);
                //gl = canvas.getContext("webgl") || canvas.getContext("experimental-webgl");
                this.mGL = this.mCvs.getContext('experimental-webgl');
                if (null == this.mGL) {
                    alert("Error: Your browser does not appear to support WebGL.");
                }
                //this.mmatProj = EngineCore.Matrix.PerspectiveFovLH(45, 1, 0.1, 1000.0);            
            } catch (e) {
                alert(e);
            }

            this.mShader = new Shader(this.mGL);
            this.mShader.initShader();
            this.mScene = new Scene();
        }

        createUI() {
            //var css = "button {cursor:pointer;}";
            //var options = { themeRoot: "./css/", themeGUI: "default" };
            //this.mUiMgr = new Fisp.UIMgr(this.mCvs, css, options);
            //var wnd = new Fisp.UIWindow("wnd", { x: 0, y: 0, w: 400, h: 600, textTitle: '主对话框', titleColor: 'rgba(255,255,255,1.0)', backgroundColor: "rgba(0,0,0,0.2)" }, this.mUiMgr);
            //wnd.setVisible(true, false);
            //var pnl = new Fisp.UIPanel("pnl", { x: 0, y: 100, w: 400, h: 400, backgroundColor: "rgba(5,0,0,0.4)" }, this.mUiMgr, null, false);
            //wnd.add(pnl);
            //pnl.setVisible(true, false);
            ////var dlg = new Fisp.UIDialog("dlg", { x: 0, y: 0, w: 400, h: 600, backgroundColor: "rgba(0,0,0,0.2)" }, guiMgr, null, true);
            ////dlg.setVisible(true, true);
            //var fun = function () { alert('clicked'); };
            //var opt = { x: 0, y: 40, w: 200, h: 40 };
            //var btn = new Fisp.UIButton("btn", opt, this.mUiMgr, fun, false);
            //wnd.add(btn);
            //var lab = new Fisp.UILabel("lab", { x: 5, y: 85, w: 100, h: 80, text: "lable 中文呢test!", color: 'rgba(255,255,255,1.0)' }, this.mUiMgr, false);
            //wnd.add(lab);
            //var txt = new Fisp.UIText("txt", { x: 5, y: 100, size: 24, text: "测试界面文本" }, this.mUiMgr, false);
            //pnl.add(txt);
            //var tex = new Fisp.UITexture("tex", "data/image/blendRGB_4.png", { x: 0, y: 150, w: 100, h: 50 }, this.mUiMgr, fun, false);
            //pnl.add(tex);
            //var edit = new Fisp.UITextEdit("edit", { x: 5, y: 210, w: 10, h: 2, size:24, value:"初始内容为空"}, this.mUiMgr, fun, false);
            //pnl.add(edit);
            //var fun = function () { alert(check.isChecked()) };
            //var check = new Fisp.UICheckbox("check", {x:5, y:300, size:2}, this.mUiMgr, fun, false);
            //pnl.add(check);
            //var fun = function () { alert(radio.isChecked()) };
            //var radio = new Fisp.UIRadiobox("radio", { x: 45, y: 300, size: 2 }, this.mUiMgr, fun, false);
            //pnl.add(radio);
            ////var clr = new Fisp.UIColor("clr", { x: 5, y: 350, w: 100, h: 50 }, this.mUiMgr, fun, false);
            ////pnl.add(clr);
            //var prg = new Fisp.UIProgress("prg", { x: 5, y: 350, w: 80, h: 5 }, this.mUiMgr, fun, false);
            //pnl.add(prg);
            //prg.setValue(44);
        }

        createScene() {
            var e: Entity = new Entity(this.mGL, this.mShader.mPgmBase);
            e.build();
            this.mScene.addEntity(e);
        }

        onUpdate() {
        }

        onRender(delta) {
            //var r = Math.random(); var g = Math.random(); var b = Math.random();
            this.mGL.clearColor(0.3, 0.2, 0.5, 1.0);
            this.mGL.clear(this.mGL.COLOR_BUFFER_BIT);
            this.mGL.viewport(0, 0, this.mCvs.width, this.mCvs.height);
            var m: Matrix = 0;

            //mat4.perspective(45, this.mCvs.width / this.mCvs.height, 0.1, 1000.0, this.mmatProj);
            //mat4.identity(this.mmatView);
            //mat4.translate(this.mmatView, this.mmatView, [0, 0, -2.0]);
            this.mScene.draw();
        }

        destroy() {
            this.mGL.deleteShader(this.mVS);
            this.mGL.deleteShader(this.mPS);
            this.mGL.deleteProgram(this.mProgram);
        }

        onresize() {
        }

    }
}