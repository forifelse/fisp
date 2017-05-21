namespace Fisp {
    export class Entity {
        mGL: WebGLRenderingContext = null;
        mVB: WebGLBuffer = null;
        mColorBfr: WebGLBuffer = null;
        mPgm: WebGLProgram = null;
        //
        mvPos: Array<number> = null;
        mvColor: Array<number> = null;
        //
        mvTemp: number = 0;

        constructor(gl: WebGLRenderingContext, pgm: WebGLProgram) {
            this.mGL = gl;
            this.mPgm = pgm;
        }

        create(gl, pgm) {
            this.mGL = gl;
            this.mPgm = pgm;
        }

        build() {
            this.mvPos = [
                -0.5, 0.5, 0.0, 0.0, 0.0, 0.0, -0.5, -0.5, 0.0, //left triangle
                0.5, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, -0.5, 0.0    //right triangle
            ];
            this.mVB = this.mGL.createBuffer();
            this.mGL.bindBuffer(this.mGL.ARRAY_BUFFER, this.mVB);
            this.mGL.bufferData(this.mGL.ARRAY_BUFFER, new Float32Array(this.mvPos), this.mGL.STATIC_DRAW);
            //
            this.mvColor = [
                1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0,    //red left triangle 
                0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0     //blue right triangle 
            ];
            this.mColorBfr = this.mGL.createBuffer();
            this.mGL.bindBuffer(this.mGL.ARRAY_BUFFER, this.mColorBfr);
            this.mGL.bufferData(this.mGL.ARRAY_BUFFER, new Float32Array(this.mvColor), this.mGL.STATIC_DRAW);
        }

        update() {
            this.mvPos[4] = Math.sin(this.mvTemp);//Math.random();
            this.mvPos[13] = this.mvPos[4];
            this.mvTemp += 0.05;
            this.mvPos[3] = Math.cos(this.mvTemp);
            this.mvPos[12] = this.mvPos[3];
            //this.mvPos[2] = Math.random();
            this.mGL.bindBuffer(this.mGL.ARRAY_BUFFER, this.mVB);
            this.mGL.bufferData(this.mGL.ARRAY_BUFFER, new Float32Array(this.mvPos), this.mGL.DYNAMIC_DRAW);

            //this.mvColor[0] = Math.random();
            //this.mvColor[1] = Math.random();
            //this.mvColor[2] = Math.random();
            //this.mGL.bindBuffer(this.mGL.ARRAY_BUFFER, this.mColorBfr);
            //this.mGL.bufferData(this.mGL.ARRAY_BUFFER, new Float32Array(this.mvColor), this.mGL.DYNAMIC_DRAW);

        }

        draw() {
            var vertexPositionAttribute = this.mGL.getAttribLocation(this.mPgm, "aVertexPosition");
            this.mGL.enableVertexAttribArray(vertexPositionAttribute);
            this.mGL.bindBuffer(this.mGL.ARRAY_BUFFER, this.mVB);
            this.mGL.vertexAttribPointer(vertexPositionAttribute, 3, this.mGL.FLOAT, false, 0, 0);
            //
            var colorAttribute = this.mGL.getAttribLocation(this.mPgm, "aVertexColor");
            this.mGL.enableVertexAttribArray(colorAttribute);
            this.mGL.bindBuffer(this.mGL.ARRAY_BUFFER, this.mColorBfr);
            this.mGL.vertexAttribPointer(colorAttribute, 3, this.mGL.FLOAT, false, 0, 0);
            //
            this.mGL.drawArrays(this.mGL.TRIANGLES, 0, 6);

            //void clear(GLbitﬁeld mask)
            //void drawArrays(GLenum mode, GLint ﬁrst, GLsizei count)
            //void drawElements(GLenum mode, GLsizei count, GLenum type, GLintptr offset) 

        }

    }
}