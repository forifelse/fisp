/// <reference path="enginecore.d.ts" />
namespace Fisp {
    export class CustomMesh {
        mMesh: EngineCore.Mesh;
        mData: EngineCore.VertexData;

        constructor(name: string, engine: IEngine) {
            this.mMesh = engine.createMesh(name);
            this.mData = new EngineCore.VertexData();
        }

        setVertexData(pos: number[] | Float32Array, nor: number[] | Float32Array, clr: number[] | Float32Array, uv: number[] | Float32Array, uv2?: number[] | Float32Array, bone?: number[] | Float32Array, weight?: number[] | Float32Array) {
            if (null == pos)
                return;
            //this.mData.positions = pos;
            //this.mData.normals = nor || null;
            //this.mData.colors = clr || null;
            //this.mData.uvs = uv || null;
            //this.mData.uvs2 = uv2 || null;
            //this.mData.matricesIndices = bone || null;
            //this.mData.matricesWeights = weight || null;  
                      
            this.mMesh.setVerticesData(EngineCore.VertexBuffer.PositionKind, pos, true);
            if(nor)
                this.mMesh.setVerticesData(EngineCore.VertexBuffer.NormalKind, nor, true);
            if (clr)
                this.mMesh.setVerticesData(EngineCore.VertexBuffer.ColorKind, clr, true);
            if (uv)
                this.mMesh.setVerticesData(EngineCore.VertexBuffer.UVKind, uv, true);
            if (uv2)
                this.mMesh.setVerticesData(EngineCore.VertexBuffer.UV2Kind, uv2, true);
            if (bone)
                this.mMesh.setVerticesData(EngineCore.VertexBuffer.MatricesIndicesKind, bone, true);
            if (weight)
                this.mMesh.setVerticesData(EngineCore.VertexBuffer.MatricesWeightsKind, weight, true);
        }

        setIndexData(index: number[] | Int32Array) {
            //this.mData.indices = index;
            if (index)
                this.mMesh.setIndices(index);

        }

        updatePos(func: (posArray: number[])=>void) {
            this.mMesh.updateMeshPositions(func || this.updatePosFunc, true);
        }

        updatePosFunc(posArray: number[]) {
        }
    }

    export class RdrImp extends IEngine {
        mCore: EngineCore.Engine;
        mScene: EngineCore.Scene;
        //mCamera: EngineCore.FreeCamera;
        mCamera: EngineCore.ArcRotateCamera;
        mSkyLight: any;
        mDireLight: any;
        mPointLight: any;
        mSpotLight: any;
        mSSAO: any;

        constructor(cvs: HTMLCanvasElement) {
            super();
            if (!cvs) {
                alert("canvas/webgl not support!");
                return;
            }
            this.mCore = new EngineCore.Engine(cvs, true);
            this.mScene = new EngineCore.Scene(this.mCore);
            this.mScene.clearColor = new EngineCore.Color4(0, 0, 0, 0);
            //this.mCamera = new EngineCore.FreeCamera("camera1", new EngineCore.Vector3(0, 30, -25), this.mScene);
            //this.mCamera.rotation = new EngineCore.Vector3(0, 0, 0);
            ////this.mCamera.setTarget(EngineCore.Vector3.Zero());
            //this.mCamera.attachControl(cvs, false);

            this.mCamera = new EngineCore.ArcRotateCamera("ArcRotateCamera", 1, 0.8, 10, new EngineCore.Vector3(0, 0, 0), this.mScene);
            this.mCamera.attachControl(cvs, false);
        }

        create() {
            this.defSetting();
            this.createScene();
        }

        destroy() {
            this.mScene.dispose();
            this.mCore.dispose();
        }

        defSetting() {
            this.createSkyLight('skylight');
            this.createDirectionalLight('direlight');
            ////this.mScene.setCamLit(Fisp.mcLight.createCamLit());
            //this.useSSAO(true);
            //this.enableCollision(false);
            ////this.mScene.enableFog(false);
        }

        createScene() {
            //this.createSkyBox("skybox", "skybox");
            //this.createTerrain('terrain', 'grass.jpg', 64, 64);
            //this.createEditorGrid();
            var light = new EngineCore.HemisphericLight("light1", new EngineCore.Vector3(0, 1, 0), this.mScene);
            light.intensity = 0.5;
        }

        renderLoop() {
            this.mScene.render();
        }

        resize() {
            this.mCore.resize();
        }

        stop() {
        }

        fps(): number {
            return this.mCore.getFps();
        }

        createSkyLight(name) {
            this.mSkyLight = new EngineCore.HemisphericLight(name, new EngineCore.Vector3(0, 1, 0), this.mScene);
            this.mSkyLight.diffuse = new EngineCore.Color3(0.1, 0.1, 0.1);
            this.mSkyLight.specular = new EngineCore.Color3(1, 1, 1);
            this.mSkyLight.groundColor = new EngineCore.Color3(0.4, 0.4, 0.4);//new EngineRender.Color3(0, 0, 0);
            //return this.mSkyLight;
        }

        createDirectionalLight(name) {
            this.mDireLight = new EngineCore.DirectionalLight(name, new EngineCore.Vector3(-1, -1, -1), this.mScene);
            this.mDireLight.diffuse = new EngineCore.Color3(1, 1, 1);
            this.mDireLight.specular = new EngineCore.Color3(1, 1, 1);
        }

        createPointLight(name) {
            this.mPointLight = new EngineCore.PointLight(name, new EngineCore.Vector3(1, 10, 1), this.mScene);
            this.mPointLight.diffuse = new EngineCore.Color3(1, 0, 0);
            this.mPointLight.specular = new EngineCore.Color3(1, 1, 1);
        }

        createSpotLight(name) {
            this.mSpotLight = new EngineCore.SpotLight(name, new EngineCore.Vector3(0, 30, -10), new EngineCore.Vector3(0, -1, 0), 0.8, 2, this.mScene);
            //this.mSpotLight.diffuse = new EngineRender.Color3(1, 0, 0);
            //this.mSpotLight.specular = new EngineRender.Color3(1, 1, 1);
        }

        SSAO(bEnable) {
            if (bEnable) {
                //thisptr.mSSAO = new EngineRender.SSAORenderingPipeline('ssaopipeline', thisptr.mScene.scene(), { ssaoRatio: 0.5, combineRatio: 1.0 }, thisptr.mvCamera[thisptr.muCamIdx]);
                this.mSSAO = new EngineCore.SSAORenderingPipeline('ssaopipeline', this.mScene, 0.45);
                this.mScene.postProcessRenderPipelineManager.attachCamerasToRenderPipeline("ssaopipeline", this.mCamera);
            }
            else {
                this.mSSAO.dispose();
                this.mScene.postProcessRenderPipelineManager.disableEffectInPipeline("ssaopipeline", this.mSSAO.SSAOCombineRenderEffect, this.mCamera);
            }
        }

        createMesh(name) {
            var mesh = new EngineCore.Mesh(name, this.mScene);
            return mesh;
        }

        createSkyBox(name, boxImg, underGround?, rateY?, size?) {
            boxImg = boxImg || "skybox";
            //underGround = underGround || null;
            rateY = rateY || 1;
            size = size || 1024;
            var skybox = EngineCore.Mesh.CreateBox(name, size, this.mScene, false, EngineCore.Mesh.BACKSIDE);
            skybox.infiniteDistance = true;
            skybox.scaling.y *= rateY;
            skybox.position.y = (underGround == undefined || underGround == null || underGround < 0) ? 0 : (size * rateY * 0.5 - underGround);
            //skybox.userData = new Object();
            //this.mSkyBox = skybox;

            var mate = new EngineCore.StandardMaterial(boxImg, this.mScene);
            mate.backFaceCulling = true;
            //mate.ambientColor = new EngineCore.Color3(1.0, 1.0, 1.0);
            mate.diffuseColor = new EngineCore.Color3(0, 0, 0);
            mate.specularColor = new EngineCore.Color3(0, 0, 0);
            mate.reflectionTexture = new EngineCore.CubeTexture("data/source/" + boxImg, this.mScene);
            mate.reflectionTexture.coordinatesMode = EngineCore.Texture.SKYBOX_MODE;
            //return mate;
            skybox.material = mate;
            return skybox;
        }

        createTerrain(name, texImg, uScale = 1, vScale = 1, bCollision = true, bUpdate  = false) {
            bUpdate = bUpdate || false;
            var ground = EngineCore.Mesh.CreateGround(name, 1024, 1024, 1, this.mScene, bUpdate);
            var mate = new EngineCore.StandardMaterial("texTerrain", this.mScene);
            mate.ambientColor = new EngineCore.Color3(0.1, 0.1, 0.1);
            mate.diffuseColor = new EngineCore.Color3(0.4, 1.0, 0.4);
            mate.specularColor = new EngineCore.Color3(0.01, 0.01, 0.01);
            if (!(texImg && texImg.length > 1)){
                texImg = 'grass.jpg';
            }
            mate.diffuseTexture = new EngineCore.Texture("data/source/" + texImg, this.mScene);
            (<any>mate.diffuseTexture).uScale = uScale;
            (<any>mate.diffuseTexture).vScale = vScale;
            ground.material = mate;
            
            ground.receiveShadows = true;
            ground.checkCollisions = bCollision;
            //ground.optimize(16);
            //return ground;
        }

        createTerrainFromHightMap(name, texImg, heightmapImg, uScale?, vScale?, xsize?, zsize?, subdiv?, minHight?, maxHight?, bCollision?, bUpdate?) {
            uScale = uScale || 1; vScale = vScale || 1;
            xsize = xsize || 1024; zsize = zsize || 1024;
            subdiv = subdiv || 32;
            minHight = minHight || 0; maxHight = maxHight || 128;
            bCollision = bCollision || true;
            bUpdate = bUpdate || false;
            var ground = EngineCore.Mesh.CreateGroundFromHeightMap(name, Fisp.gRoot.mCfg.mcfgPath.dataPath + "data/source/" + heightmapImg, xsize, zsize, subdiv, minHight, maxHight, this.mScene, bUpdate, function (groundmesh) { });//, successCallback);
            var mate = new EngineCore.StandardMaterial("texTerrainHM", this.mScene);
            mate.diffuseTexture = new EngineCore.Texture("data/source/" + texImg, this.mScene);
            (<any>mate.diffuseTexture).uScale = uScale;
            (<any>mate.diffuseTexture).vScale = vScale;
            mate.specularColor = new EngineCore.Color3(0.1, 0.1, 0.1);
            ground.material = mate;
            ground.receiveShadows = true;
            ground.checkCollisions = bCollision;
            //ground.optimize(16);
            //ground.userData = new Object();
            return ground;
        }

        water(name) {
            //name = name || "water";
            //var mesh = EngineCore.Mesh.CreateGround(name, 8192, 8192, 1, this.mScene, true);
            //mesh.material = Fisp.mcMaterial.wave();
            ////mesh.material = Fisp.mcMaterial.mirror();
            //mesh.position.y = -1;
            //mesh.update = function (delta) {
            //    //var wvp = this.getWorldMatrix().multiply(Fisp.mcCamera.viewMatrix());
            //    //wvp = wvp.multiply(Fisp.mcCamera.projMatrix());
            //    //this.material.setMatrix("worldViewProjection", wvp);
            //    this.material.update(delta);
            //}
            ////this.mScene.mupdatelist.push(mesh);
            ////mesh.userData = new Object();
            //return mesh;
        }

        createEditorGrid(size = 4096, subdiv = 64) {
            //size = size || 4096; subdiv = subdiv || 64;
            var sub = Math.floor(subdiv * 0.5);
            var step = size / (sub * 2);
            var pts = [];
            var pmax = sub * step;
            var y = -0.00001;
            pts = [new EngineCore.Vector3(-pmax - 4 * step, y, 0), new EngineCore.Vector3(pmax + 4 * step, y, 0), new EngineCore.Vector3(pmax + step * 0.5, y, step * 0.25)];
            var meshsubx = EngineCore.Mesh.CreateLines("editorGridx", pts, this.mScene);
            meshsubx.color = new EngineCore.Color3(0.7, 0.0, 0.0);
            pts = [new EngineCore.Vector3(0, y, -pmax - 4 * step), new EngineCore.Vector3(0, y, pmax + 4 * step), new EngineCore.Vector3(-step * 0.25, y, pmax + step * 0.5)];
            var meshsubz = EngineCore.Mesh.CreateLines("editorGridx", pts, this.mScene);
            meshsubz.color = new EngineCore.Color3(0.0, 0.0, 0.7);
            var clr = new EngineCore.Color3(0.5, 0.5, 0.5);
            var x;
            for (var i = 0; i < sub; i++) {
                x = (i + 1) * step;
                pts = [new EngineCore.Vector3(x, y, -pmax), new EngineCore.Vector3(x, y, pmax)];
                var meshsubz = EngineCore.Mesh.CreateLines("editorGridx", pts, this.mScene);
                meshsubz.color = clr;
                pts = [new EngineCore.Vector3(-x, y, -pmax), new EngineCore.Vector3(-x, y, pmax)];
                var meshsubz = EngineCore.Mesh.CreateLines("editorGridx", pts, this.mScene);
                meshsubz.color = clr;
                //
                pts = [new EngineCore.Vector3(-pmax, y, x), new EngineCore.Vector3(pmax, y, x)];
                var meshsubx = EngineCore.Mesh.CreateLines("editorGridx", pts, this.mScene);
                meshsubx.color = clr;
                pts = [new EngineCore.Vector3(-pmax, y, -x), new EngineCore.Vector3(pmax, y, -x)];
                var meshsubx = EngineCore.Mesh.CreateLines("editorGridx", pts, this.mScene);
                meshsubx.color = clr;
            }
        }

        addSkeleton(name, fileName, objName, bCastShadow, animate?, pos?, scale?, bReceiveShadow?, bSimplify?) {
            bCastShadow = bCastShadow || true;
            animate = animate || null;
            pos = pos || new EngineCore.Vector3(0, 0, 0);
            scale = scale || new EngineCore.Vector3(1, 1, 1);
            bReceiveShadow = bReceiveShadow || true;
            bSimplify = bSimplify || false;
            var that = this;
            EngineCore.SceneLoader.ImportMesh(objName, "data/source/", fileName, this.mScene,
                function (newMeshes, particleSystems, skeletons) {
                    // add new meshs
                    if (newMeshes && newMeshes.length > 0) {
                        for (var i = 0; i < newMeshes.length; i++) {
                            newMeshes[i].position.x = pos.x;
                            newMeshes[i].position.y = pos.y;
                            newMeshes[i].position.z = pos.z;
                            newMeshes[i].scaling = scale;
                            if (animate) {
                                //Fisp.mcAnimate.rotate(newMeshes[i]);
                                if (i == 1) {
                                    animate.rotate(newMeshes[i]);
                                }
                            }
                            if (bCastShadow && that.mDireLight.castShadow) {
                                //that.mDireLight.castShadow(newMeshes[i]);
                            }
                            newMeshes[i].receiveShadows = bReceiveShadow;
                            newMeshes[i].name = name + ((i != 0) ? i : "");
                            //newMeshes[i].layerMask = 1;
                            //newMeshes[i].userData = new Object();
                            //
                            //if (bSimplify) {
                            //    newMeshes[i].simplify([{ quality: 0.9, distance: 20 }, { quality: 0.7, distance: 40 }, { quality: 0.5, distance: 70 }, { quality: 0.3, distance: 90 }, { quality: 0.1, distance: 100 }],
                            //        false, EngineCore.SimplificationType.QUADRATIC, function () {
                            //            alert(fileName + "LOD finisehd, let's have a beer!");
                            //        });
                            //}
                            //
                        }
                        //meshs = newMeshes;
                    }
                    if (skeletons && skeletons.length > 0) {
                        that.mScene.beginAnimation(skeletons[0], 0, 120, true, 1.0);
                        newMeshes[0].scaling = scale;
                        //that.mAvator = newMeshes[0];
                        //that.mAvator.scaling = new EngineCore.Vector3(0.05, 0.05, 0.05);
                    }
                },
                function () {// progresss
                },
                function (scene, msg, e) {// error
                    //gMsgbox.showMsg(msg);
                });
        }

        customMesh(name: string, pos: Float32Array, nor: Float32Array, clr: Float32Array, uv: Float32Array, uv2?: Float32Array, bone?: Float32Array, weight?: Float32Array) {
            
        }

    }
}