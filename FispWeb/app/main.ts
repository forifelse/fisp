namespace Fisp {
    export class AppLgc {
        optCallback: any;
        //mDlgTop: Fisp.DlgTop;
        //mDlgMain: Fisp.DlgMain;
        //mDlgEditScene: Fisp.DlgEditScene;
        //mDlgEntityProp: Fisp.DlgEntityProperty;
        //mDlgChat: Fisp.DlgChat;

        constructor() {
            this.optCallback = new Object();
            this.optCallback.onSetup = this.onSetup;
            this.optCallback.onCreate = this.onCreate;
            this.optCallback.onBuildScene = this.onBuildScene;
            this.optCallback.onBuildUi = this.onBuildUi;
            this.optCallback.onUpdate = this.onUpdate;
            this.optCallback.onPicked = this.onPicked;
            this.optCallback.onResize = this.onResize;
            //
            //this.mDlgTop = null;
            //this.mDlgMain = null;
            //this.mDlgEditScene = null;
            //this.mDlgEntityProp = null;
            //this.mDlgChat = null;
        }

        onSetup() {
            alert('onSetup');
        }

        onCreate() {
            alert('onCreate');
        }

        onBuildScene() {
            //gRoot.mEngineImp.createSkyBox('skybox_objname', "skybox");
            //gRoot.mEngineImp.createTerrain('grass_objname', 'grass.jpg', 32, 32, true, false);
            //
            var bSimplify = false;
            var pos = new EngineCore.Vector3(0, 0, 0);
            var scale = new EngineCore.Vector3(1.0,1.0,1.0);//(0.05, 0.05, 0.05);
            //gRoot.mEngineImp.addSkeleton('character_objname', "dude.3d", null, true, null, pos, scale, true, bSimplify);
            gRoot.mEngineImp.addSkeleton('character_objname', "test.3d", null, true, null, pos, scale, true, bSimplify);

        }

        onBuildUi(uiMgr) {
            var that = this;
            //this.mDlgTop = new Fisp.DlgTop(uiMgr);
            //this.mDlgMain = new Fisp.DlgMain(uiMgr);
            //this.mDlgTop.mdlgMain = this.mDlgMain;
            //this.mDlgEditScene = new Fisp.DlgEditScene(uiMgr);
            //this.mDlgEntityProp = new Fisp.DlgEntityProperty();
            //this.mDlgChat = new Fisp.DlgChat(uiMgr);

            //uiMgr.regUserDlg(this.mDlgTop);
            //uiMgr.regUserDlg(this.mDlgMain);
            //uiMgr.regUserDlg(this.mDlgEditScene);
            //uiMgr.regUserDlg(this.mDlgEntityProp);
            //uiMgr.regUserDlg(this.mDlgChat);
        }

        onUpdate(delta: number) {
        }

        onPicked() {
        }

        onResize(evt) {
            //if (null != this.mDlgTop) {
            //    this.mDlgTop.resize(evt);
            //}
        }

    }

    //
    export class LgcEvent {

        constructor() {
        }

        procCfgData(str) {
        }

        editScene() {
        }

        editMode(bEdit) {
        }

        exitEdit() {
        }

        newScene(strName: string) {
            if (strName && strName.length > 0) {
                var cnt = gUser.mUserData.mSceneList.push(strName);
                //this.mDlgEditScene.newScene(cnt - 1, strName);
                //var msg = "newscene:" + strName;
                //gRoot.mFrame.mNet.sendMsg(msg, 1, gUser.mstrName);
            }
        }

        delScene() {
        }

        getPlaceGlobalList() {
            var list = null;
            if (null != gRoot.mCfg.mcfgEdit) {
                list = gRoot.mCfg.mcfgEdit.PlaceGlobal;
            }
            return list;
        }

        getPlaceBasicList() {
            var list = null;
            if (null != gRoot.mCfg.mcfgEdit) {
                list = gRoot.mCfg.mcfgEdit.PlaceBasic;
            }
            return list;
        }

        getPlaceCommonList() {
            var list = null;
            if (null != gRoot.mCfg.mcfgEdit) {
                list = gRoot.mCfg.mcfgEdit.PlaceBuild;
            }
            return list;
        }

        getImgList() {
            var list = null;
            if (null != gRoot.mCfg.mcfgEdit) {
                list = gRoot.mCfg.mcfgEdit.ImgList;
            }
            return list;
        }

        getAnimFlagList() {
            var list = null;
            if (null != gRoot.mCfg.mcfgEdit) {
                list = gRoot.mCfg.mcfgEdit.AnimFlag;
            }
            return list;
        }

        placeEntityGlobal(id) {
            var size = 10;
            var bSimplify = false;
            var pos = new EngineCore.Vector3(0, 0, 0);
            var name = id + '_obj_' + gUser.entityCount();
            switch (id) {
                case "skybox":
                    gRoot.mEngineImp.createSkyBox(name, "skybox");
                    break;
                case "ground":
                    gRoot.mEngineImp.createTerrain(name, 'grass.jpg', 32, 32, true, false);
                    break;
                case "groundHM":
                    gRoot.mEngineImp.createTerrainFromHightMap(name, 'ground.jpg', 'heightmap.png', 64, 64, 1024, 1024, 32, -32, 64, true, false);
                    break;
                case "groundUL":
                    var mesh = new CustomMesh(name, gRoot.mEngineImp);
                    mesh.setVertexData([0, 0, 0, 1, 1, 1, 2, 0, 0], [0, 1, 0, 1, 1, 0, 1, 0, 0], [1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1], null);
                    mesh.setIndexData([0, 2, 1]);
                    mesh.mMesh.scaling = new EngineCore.Vector3(14, 14, 14);
                    //gMsgbox.showMsg("Unlimited");
                    break;
                case "water":
                    //Fisp.mcMesh.water(name);
                    break;
                case "character":
                    var bSimplify = false;
                    var pos = new EngineCore.Vector3(0, 0, 0);
                    var scale = new EngineCore.Vector3(0.05, 0.05, 0.05);
                    gRoot.mEngineImp.addSkeleton(name, "dude.3d", null, true, null, pos, scale, true, bSimplify);
                    break;
                case "litSky":
                    gRoot.mEngineImp.createSkyLight(name);
                    break;
                case "litDir":
                    gRoot.mEngineImp.createDirectionalLight(name);
                    break;
                case "litPoint":
                    gRoot.mEngineImp.createPointLight(name);
                    break;
                case "litSpot":
                    gRoot.mEngineImp.createSpotLight(name);
                    break;
            }
            gUser.addEntity('global', name);
            return name;
        }

        placeEntityBasic(id) {
            var size = 10;
            var bSimplify = false;
            var pos = new EngineCore.Vector3(0, 0, 0);
            var name = id + '_obj_' + gUser.entityCount();
            switch (id) {
                case "triangle":
                    var mesh = new CustomMesh(name, gRoot.mEngineImp);
                    mesh.setVertexData([0, 0, 0, 1, 1, 1, 2, 0, 0], [0, 1, 0, 1, 1, 0, 1, 0, 0], [1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1], null);
                    mesh.setIndexData([0, 2, 1]);
                    mesh.mMesh.scaling = new EngineCore.Vector3(14, 14, 14);
                    break;
            }
            gUser.addEntity('basic', name);
            return name;
        }

        placeEntityBuild(id) {
            var size = 10;
            var bSimplify = false;
            var pos = new EngineCore.Vector3(0, 0, 0);
            var name = id + '_obj_' + gUser.entityCount();
            switch (id) {
                case "triangle":
                    var mesh = new CustomMesh(name, gRoot.mEngineImp);
                    mesh.setVertexData([0, 0, 0, 1, 1, 1, 2, 0, 0], [0, 1, 0, 1, 1, 0, 1, 0, 0], [1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1], null);
                    mesh.setIndexData([0, 2, 1]);
                    mesh.mMesh.scaling = new EngineCore.Vector3(14, 14, 14);
                    break;
            }
            gUser.addEntity('basic', name);
            return name;
        }

        placeEntityMachine(id) {
            var size = 10;
            var bSimplify = false;
            var pos = new EngineCore.Vector3(0, 0, 0);
            var name = id + '_obj_' + gUser.entityCount();
            switch (id) {
                case "triangle":
                    var mesh = new CustomMesh(name, gRoot.mEngineImp);
                    mesh.setVertexData([0, 0, 0, 1, 1, 1, 2, 0, 0], [0, 1, 0, 1, 1, 0, 1, 0, 0], [1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1], null);
                    mesh.setIndexData([0, 2, 1]);
                    mesh.mMesh.scaling = new EngineCore.Vector3(14, 14, 14);
                    break;
            }
            gUser.addEntity('basic', name);
            return name;
        }

    }
    export var gLgcEvent: LgcEvent = new LgcEvent();
}