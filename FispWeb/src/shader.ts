namespace Fisp {
    export class Shader {
        mGL: WebGLRenderingContext = null;
        mPgmBase: WebGLProgram = null;
        mVS: WebGLShader = null;
        mPS: WebGLShader = null;

        constructor(gl: WebGLRenderingContext) {
            this.mGL = gl;
        }

        create(gl) {
            this.mGL = gl;
        }

        initShader() {
            var vsCode = this.baseVS();
            var psCode = this.basePS();
            this.mVS = this.makeShader(vsCode, this.mGL.VERTEX_SHADER);
            this.mPS = this.makeShader(psCode, this.mGL.FRAGMENT_SHADER);
            this.mPgmBase = this.mGL.createProgram();
            this.mGL.attachShader(this.mPgmBase, this.mVS);
            this.mGL.attachShader(this.mPgmBase, this.mPS);
            this.mGL.linkProgram(this.mPgmBase);
            if (!this.mGL.getProgramParameter(this.mPgmBase, this.mGL.LINK_STATUS)) {
                alert("Unable to initialize the shader program.");
            }
            this.mGL.useProgram(this.mPgmBase);
        }

        makeShader(src, type) { //compile the shader
            var shader = this.mGL.createShader(type);
            this.mGL.shaderSource(shader, src);
            this.mGL.compileShader(shader);
            if (!this.mGL.getShaderParameter(shader, this.mGL.COMPILE_STATUS)) {
                alert("Error compiling shader: " + this.mGL.getShaderInfoLog(shader));
            }
            return shader;
        }

        baseVS() {
            var src =
                'attribute vec3 aVertexPosition;' +
                'attribute vec3 aVertexColor;' +
                'varying highp vec4 vColor; ' +
                'void main(void) {' +
                'gl_Position = vec4(aVertexPosition, 1.0);' +
                'vColor = vec4(aVertexColor, 1.0);' +
                '}'
                ;
            return src;
        }

        basePS() {
            var src =
                'varying highp vec4 vColor; ' +
                'void main(void) {' +
                'gl_FragColor = vColor;' +
                '}';
            return src;
        }
    }
}