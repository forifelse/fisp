namespace Fisp {
    export class SysConfig {
        mstrDataPath: string = null;
        mcfgPath: any = null;
        mcfgEdit: any = null;
        mObjGlobal: any = null;
        mObjBasic: any = null;
        mObjBuild: any = null;
        mObjMachine: any = null;

        constructor() {
            this.mstrDataPath = 'data/';
            this.mcfgPath = null;
            this.mcfgEdit = null;
            this.mObjGlobal = null;
            this.mObjBasic = null;
            this.mObjBuild = null;
            this.mObjMachine = null;
        }

        getRootPath() {
            var strFullPath = window.document.location.href;
            var strPath = window.document.location.pathname;
            var pos = strFullPath.indexOf(strPath);
            var prePath = strFullPath.substring(0, pos);
            var postPath = strPath.substring(0, strPath.substr(1).indexOf('/') + 1);
            return (prePath + postPath);
        }

        getRootPath2() {
            var pathName = window.location.pathname.substring(1);
            var webName = pathName == '' ? '' : pathName.substring(0, pathName.indexOf('/'));
            //return window.location.protocol + '//' + window.location.host + '/'+ webName + '/';
            return window.location.protocol + '//' + window.location.host + '/' + webName;
        } 

        loadCfg() {
            var that = this;
            //var vdDir = this.getRootPath();
            //that.mstrDataPath = this.getRootPath2();

            var procData = function (data: string) {
                that.mcfgPath = JSON.parse(data);
            }
            //NetData.getData('fispweb.json', procData);
            //var procData = function (data: string) {
            //    that.mcfgEdit = JSON.parse(data);
            //}
            //NetData.getData(that.mstrDataPath + 'web/config/cfg.json', procData);

            //var procData = function (data: string) {
            //    that.mObjGlobal = JSON.parse(data);
            //}
            //NetData.getData(that.mstrDataPath + 'web/config/objglobal.json', procData);
            //var procData = function (data: string) {
            //    that.mObjBasic = JSON.parse(data);
            //}
            //NetData.getData(that.mstrDataPath + 'web/config/objbasic.json', procData);
            //var procData = function (data: string) {
            //    that.mObjBuild = JSON.parse(data);
            //}
            //NetData.getData(that.mstrDataPath + 'web/config/objbuilding.json', procData);
            //var procData = function (data: string) {
            //    that.mObjMachine = JSON.parse(data);
            //}
            //NetData.getData(that.mstrDataPath + 'web/config/objmachine.json', procData);
        }
    }

    export class UserData {
        mFmt: FormData;
        mID: string;
        mName: string;
        mSceneList: Array<string>;

        constructor() {
            this.mFmt = new FormData();
            this.mID = '';
            this.mName = '';
            this.mSceneList = [];
        }

        format() {
        }

        extract() {
        }
    }

    export abstract class IEngine {
        abstract create();
        abstract renderLoop();
        abstract stop();
        abstract resize();
        abstract fps(): number;
        abstract createSkyLight(name);
        abstract createDirectionalLight(name);
        abstract createPointLight(name);
        abstract createSpotLight(name);
        abstract SSAO(bEnable);
        abstract createMesh(name);
        abstract createSkyBox(name, boxImg, underGround?, rateY?, size?);
        abstract createTerrain(name, texImg, uScale?, vScale?, bCollision?, bUpdate?);
        abstract createTerrainFromHightMap(name, texImg, heightmapImg, uScale?, vScale?, xsize?, zsize?, subdiv?, minHight?, maxHight?, bCollision?, bUpdate?);
        abstract createEditorGrid(size?, subdiv?);
        abstract addSkeleton(name, fileName, objName, bCastShadow, animate?, pos?, scale?, bReceiveShadow?, bSimplify?);
    }
}