namespace Fisp {
    export class User {
        mbEdit: boolean;
        mbSignin: boolean;
        mstrName: string;
        mvSceneName: Array<string>;
        mstrCurScene: string;
        midxScene: number;
        mUserData: UserData;
        //
        muSceneMax: number = 4;
        //
        mstrSocketID: string;

        constructor() {
            this.mbEdit = false;
            this.mbSignin = false;
            this.mstrName = "";
            this.mvSceneName = [];
            this.mstrCurScene = "";
            this.mUserData = new UserData();
        }

        signin(id, pw) {
            if (!id || !pw) {
                return;
            }
            var msg = 'signin:' + id + ',' + pw;
            gRoot.mFrame.mNet.sendMsg(msg, 0, this.mstrName);
        }

        signup(id, pw, opt) {
            if (!id || !pw) {
                return;
            }
            opt.email = opt.email || '';
            var msg = 'signup:' + id + ',' + pw + ',' + opt.email;
            gRoot.mFrame.mNet.sendMsg(msg, 0, this.mstrName);
        }

        signout() {
            this.mstrName = '';
            this.mbSignin = false;
        }

        sceneCnt(): number {
            return this.mUserData.mSceneList.length;
            //return this.mvSceneName.length;
        }

        sceneName(idx: number): string {
            var strName = "";
            if (idx >= 0 && idx < this.mUserData.mSceneList.length) {
                strName = this.mUserData.mSceneList[idx];
            }
            return strName;
        }

        curScene(): string {
            return this.mstrCurScene;
        }

        newScene(strName) {
            var cnt = 0;
            if (strName && strName.length > 0) {
                cnt = this.mUserData.mSceneList.push(strName);
            }
            return cnt;
        }

        findScene(strName: string): boolean {
            var cnt = this.mUserData.mSceneList.length;
            if (cnt <= 0)
                return false;
            for (var i = 0; i < cnt; i++) {
                if (strName == this.mUserData.mSceneList[i]) {
                    return true;
                }
            }
            return false;
        }

        delScene(strName = ""): number {
            if (!strName || strName == "") {
                strName = this.mstrCurScene;
            }
            var cnt = this.mUserData.mSceneList.length;
            if (cnt <= 0)
                return -1;
            var idx = -1;
            for (var i = 0; i < cnt; i++) {
                if (strName == this.mUserData.mSceneList[i]) {
                    this.mUserData.mSceneList[i] = this.mUserData.mSceneList[cnt - 1];
                    idx = i;
                    break;
                }
            }
            if (idx >= 0) {
                this.mUserData.mSceneList.pop();
            }
            return idx;
        }

        selectScene(idx: number): string {
            var strScene;
            this.midxScene = -1;
            this.mstrCurScene = '';
            if (idx >= 0 && idx < this.sceneCnt()) {
                this.midxScene = idx;
                this.mstrCurScene = this.sceneName(idx);
            }
            return this.mstrCurScene;
        }

        sendMsg(strChat: string) {
            if (strChat && strChat.length > 0) {
                var msg = 'chat:' + strChat;
                var strName = (this.mbSignin) ? this.mstrName : (gLang.mString.others.visitor[gLang.muLang] + ' ' + this.mstrSocketID);
                var b = gRoot.mFrame.mNet.sendMsg(msg, 0, strName);
            }
        }

        addEntity(type, name) {
        }

        entityCount() {
        }

    }
    export var gUser: User = new User();

}