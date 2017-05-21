namespace Fisp {
    export class Scene {
        mDrawList: Array<Entity> = new Array<Entity>();

        constructor() {
        }

        addEntity(entity) {
            this.mDrawList.push(entity);
        }

        draw() {
            var cnt = this.mDrawList.length;
            for (var i = 0; i < cnt; i++) {
                this.mDrawList[i].update();
                this.mDrawList[i].draw();
            }
        }

    }
}