namespace Fisp {
    export class Input {
        static gSelf: Input;
        mptTs: any = null;
        mptCs: any = null;

        constructor() {
            Input.gSelf = this;
            this.regEvent();
            this.resetPts(null, -1);
        }

        regEvent() {
            var that = this;
            window.addEventListener('resize', function () {
                //Fisp.mcRender.onResize();
            });
            window.addEventListener('DOMContentLoaded', function () {
                that.addEvent();
            });
        }

        static explorer() {
            var explorer = window.navigator.userAgent;
            var flag = -1;//0 == ie, 1 == chrome, 2 == firefox, 3 == opera, 4 == saf
            var name = explorer;
            //ie 
            if (explorer.indexOf("Edge") >= 0 || explorer.indexOf("MSIE") >= 0) {
                flag = 0;
                name = "Edge";
            }
            //Chrome
            else if (explorer.indexOf("Chrome") >= 0) {
                flag = 1;
                name = "Chrome";
            }
            //firefox 
            else if (explorer.indexOf("Firefox") >= 0) {
                flag = 2;
                name = "Firefox";
            }
            //Opera
            else if (explorer.indexOf("Opera") >= 0) {
                flag = 3;
                name = "Opera";
            }
            //Safari
            else if (explorer.indexOf("Safari") >= 0) {
                flag = 4;
                name = "Safari";
            }
            return [flag, name];
        }

        static isPC(): boolean {
            var ua = navigator.userAgent;
            var agents = new Array("Android", "iPhone", "SymbianOS", "Windows Phone", "iPad", "iPod");
            var flag = true;
            for (var i = 0; i < agents.length; i++) {
                if (ua.indexOf(agents[i]) > 0) { flag = false; break; }
            }
            return flag;
        }

        makeFullScreen(evt) {
            // Test for each of the supported versions of full screen APIs and call 
            // either requestFullscreen or cancelFullScreen (or exitFullScreen)
            //  Structure: 
            //  Does the incoming target support requestFullscreen (or prefaced version)
            //  if (there is a fullscreen element) 
            //      then cancel or exit
            //  else request full screen mode

            var divObj = evt.target;  //  get the target element

            if (divObj.requestFullscreen)
                if (document.fullscreenElement) {
                    document.exitFullscreen();
                } else {
                    divObj.requestFullscreen();
                }
            else if (divObj.msRequestFullscreen)
                if (document.msIsFullScreen) {//.msFullscreenElement) {
                    document.msCancelFullScreen();//.msExitFullscreen();
                } else {
                    divObj.msRequestFullscreen();
                }
            else if (divObj.mozRequestFullScreen)
                if (document.mozFullScreen) {
                    document.mozCancelFullScreen();
                } else {
                    divObj.mozRequestFullScreen();
                }
            else if (divObj.webkitRequestFullscreen)
                if (document.webkitFullscreenElement) {
                    document.webkitCancelFullScreen();
                } else {
                    divObj.webkitRequestFullscreen();
                }
            //  stop bubbling so we don't get bounce back
            evt.stopPropagation();
        }

        fullscreen(bFull: boolean, ele?) {
            var docElm = document.documentElement;
            var enterFull = docElm.requestFullscreen
                || docElm.webkitRequestFullscreen
                || docElm.webkitRequestFullScreen
                || (<any>docElm).msRequestFullscreen
                || (<any>docElm).mozRequestFullScreen;

            var exitFull = document.exitFullscreen
                || document.webkitCancelFullScreen
                || document.webkitExitFullscreen
                || (<any>document).msExitFullscreen
                || (<any>document).mozCancelFullScreen;

            ele = document.body;//document.getElementById('cvsid') || ele;

            if (bFull)
                enterFull();//enterFull.call(ele);
            else
                exitFull.call(ele);
            //ele.stopPropagation();
        }

        fullscreenx(evt: Event, bFull) {
            if (bFull) {
                var docElm = document.documentElement;
                //W3C
                if (docElm.requestFullscreen) {
                    docElm.requestFullscreen();
                    alert('W3C: Fullscreen On');
                }
                //Chrome
                else if (docElm.webkitRequestFullScreen) {
                    //docElm.webkitRequestFullScreen();
                    // 对 Chrome 特殊处理，
                    // 参数 Element.ALLOW_KEYBOARD_INPUT 使全屏状态中可以键盘输入。
                    if (window.navigator.userAgent.toUpperCase().indexOf('CHROME') >= 0) {
                        //docElm.webkitRequestFullscreen(Element.ALLOW_KEYBOARD_INPUT);
                        docElm.webkitRequestFullScreen();
                    }
                    // Safari 浏览器中，如果方法内有参数，则 Fullscreen 功能不可用。
                    else {
                        docElm.webkitRequestFullScreen();
                    }
                    //alert('Chrome: ');
                }
                //IE11
                //else if (docElm.msRequestFullscreen) {
                //    docElm.msRequestFullscreen();
                //    //
                //    //var dlg = document.getElementById("rightPannel");
                //    //dlg.style.marginLeft = window.innerWidth - 314 + "px";
                //}
                //FireFox
                else if (document.mozFullScreen) {
                    document.mozFullScreen = bFull;
                    //alert('Chrome: ' + typeof (document));
                }
                //else if (docElm.mozRequestFullScreen) {
                //    docElm.mozRequestFullScreen();
                //}
            }
            else {
                if (document.exitFullscreen) {
                    document.exitFullscreen();
                }
                else if (document.webkitCancelFullScreen) {
                    document.webkitCancelFullScreen();
                }
                else if (document.msCancelFullScreen) {
                    document.msCancelFullScreen();
                }
                else if (document.mozCancelFullScreen) {
                    document.mozCancelFullScreen();
                }
            }
            
        }

        addEvent() {
            //var cvs = Fisp.mcRender.canvas();
            // cro fox
            document.addEventListener('mousedown', this.onMouseDown, false);
            document.addEventListener('mousemove', this.onMouseMove, false);
            document.addEventListener('mouseup', this.onMouseUp, false);
            //document.addEventListener('mouseout', mthis.onMouseOut, false);
            document.addEventListener('keydown', this.onKeyDown, false);
            document.addEventListener('keyup', this.onKeyUp, false);
            document.addEventListener("mozfullscreenchange", this.onFullscreen, false);
            document.addEventListener("webkitfullscreenchange", this.onFullscreen, false);
            window.addEventListener('resize', this.onResize, false);

            // IE
            document.addEventListener('onmousedown', this.onMouseDown);
            document.addEventListener('onmousemove', this.onMouseMove);
            document.addEventListener('onmouseup', this.onMouseUp);
            //document.addEventListener('onmouseout', mthis.onMouseOut, false);
            window.addEventListener('onkeydown', this.onKeyDown);
            window.addEventListener('onkeyup', this.onKeyUp);
            document.addEventListener("fullscreenchange", this.onFullscreen);
            window.addEventListener('resize', this.onResize);

            document.addEventListener('mousewheel', this.onMouseWheel, false); // IE,cro,safari
            document.addEventListener('DOMMouseScroll', this.onMouseWheel, false); // fox

            // pad
            document.addEventListener('touchstart', this.onTouchStart, true);
            document.addEventListener('touchmove', this.onTouchMove, true);
            document.addEventListener('touchend', this.onTouchEnd, true);
            document.addEventListener('touchcancel', this.onTouchCancel, true);
            window.addEventListener('resize', this.onResize, true);

            //
            oncontextmenu = function (evt) {
                evt.preventDefault();
                evt.returnValue = false;
            };
            //document.fullscreenEnabled = true;
            //document.webkitFullscreenEnabled = true;
        }

        onFullscreen() {
            //alert('onFullscreen');
        }

        onMouseDown(evt) {
            Input.gSelf.resetPts(evt, 0);
            if (evt.button == 0) {// left button
            }
            else if (evt.button == 1) {// mid button
            }
            else if (evt.button == 2) {// right button
            }
        }

        onMouseMove(evt) {
        //    var calRes = this.calMouse(evt);
        //    var bRe = [false, false, false, false];
        //    if (Fisp.mcRoot.onMouseMove) {
        //        bRe = Fisp.mcRoot.onMouseMove(evt, calRes);
        //        if (bRe[0]) { return; }
        //    }
        //    evt.preventDefault();
        //    if (Fisp.mcScene.isClicked()) {
        //        var dx = calRes.dx;
        //        var dy = calRes.dy;
        //        var cam = Fisp.mcCamera.camera();
        //        var eCam = Fisp.mcCamera.camIdx();
        //        if (0 == eCam) {
        //        }
        //        else if (1 == eCam) {
        //        }
        //        else if (2 == eCam) {
        //            if (this.mptTs.pt[2].on && !bRe[3]) {
        //                Fisp.mcAuxi.avatorOp("ry", -dx * 0.005);
        //                cam.heightOffset += dy * 0.5;
        //            }
        //        }
        //        else if (3 == eCam) {
        //            if (this.mptTs.pt[0].on && !bRe[1]) {
        //                var fy = cam.position.y;
        //                var opt = { fixY: fy };
        //                Fisp.mcAuxi.transObj(cam, "tx", -dx, { fixY: fy });
        //                Fisp.mcAuxi.transObj(cam, "tz", dy, { fixY: fy });
        //            }
        //            else if (this.mptTs.pt[1].on && !bRe[2]) {
        //                Fisp.mcAuxi.transObj(cam, "tx", -dx);
        //                Fisp.mcAuxi.transObj(cam, "ty", dy);
        //            }
        //            else if (this.mptTs.pt[2].on && !bRe[3]) {
        //                Fisp.mcAuxi.transObj(cam, "ry", -dx * 0.005);
        //                Fisp.mcAuxi.transObj(cam, "rx", -dy * 0.005);
        //            }
        //        }
        //    }
        //    //
        //    this.resetPts(evt, 0, true);
        }

        onMouseUp(evt) {
            //Fisp.mcScene.cancelClicked();
            //
            Input.gSelf.resetPts(evt, -1);
        }

        onMouseWheel(evt) {
            var dWheel = 0;
            if (evt.wheelDelta) {//IE/Opera/Chrome
                dWheel = evt.wheelDelta / 10.0;
            }
            else if (evt.detail) {//Firefox
                dWheel = evt.detail;
            }
            //var cam = Fisp.mcCamera.camera();
            //var eCam = Fisp.mcCamera.camIdx();
            //if (2 == eCam) {
            //    cam.radius += dWheel * 0.05;
            //}
            //else if (3 == eCam) {
            //    //cam.position.y += dWheel;
            //    Fisp.mcAuxi.transObj(cam, "tz", dWheel);
            //}
            //
            Input.gSelf.resetPts(evt, 0);
            evt.preventDefault();
        }

        onKeyDown(evt) {
            //if (Fisp.mcRoot.onKeyDown) {
            //    bRe = Fisp.mcRoot.onKeyDown(evt);//(evt, calRes);
            //    if (bRe) { return; }
            //}
            //var eCam = Fisp.mcCamera.camIdx();
            //if (0 == eCam) {
            //    mthis.onKeyDownFreeCam(evt);
            //}
            //else if (1 == eCam) {
            //}
            //else if (2 == eCam) {
            //    mthis.onKeyDownFollowCam(evt);
            //}
            //else if (3 == eCam) {
            //    mthis.onKeyDownFlyCam(evt);
            //}
        }

        onKeyUp(evt) {
        }

        onTouchStart = function (evt) {
            //evt.preventDefault();
            this.resetPts(evt, 1);
            //
            var calRes = this.calTouch(evt);
            var bRe = [false, false, false, false];
            //if (Fisp.mcRoot.onTouchStart) {
            //    bRe = Fisp.mcRoot.onTouchStart(evt, calRes);
            //    if (bRe[0]) { return; }
            //}
        }

        onTouchMove(evt) {
            //var calRes = this.calTouch(evt);
            //var bRe = [false, false, false, false];
            //if (Fisp.mcRoot.onTouchMove) {
            //    bRe = Fisp.mcRoot.onTouchMove(evt, calRes);
            //    if (bRe[0]) { return; }
            //}
            //evt.preventDefault();
            //if (Fisp.mcScene.isClicked()) {
            //    var dx = calRes.dx;
            //    var dy = calRes.dy;
            //    var cam = Fisp.mcCamera.camera();
            //    var eCam = Fisp.mcCamera.camIdx();
            //    if (eCam == 0) {
            //        //mthis.onTouchMoveFreeCam(evt);
            //    }
            //    else if (eCam == 1) {
            //        //mthis.onTouchMoveArcRotCam(evt);
            //    }
            //    else if (eCam == 2) {
            //        if (calRes.flag == 1 && !bRe[1]) {
            //            //var delta = 0.1;
            //            //Fisp.mcAuxi.avatorOp("tz", -delta);
            //        }
            //        else if (calRes.flag == 2 && !bRe[2]) {
            //            cam.radius -= calRes.zoom * 0.1;
            //            Fisp.mcAuxi.avatorOp("ry", calRes.spin);
            //            cam.heightOffset += calRes.pushY * 0.5;
            //        }
            //        else if (calRes.flag == 3 && !bRe[3]) {
            //        }
            //    }
            //    else if (eCam == 3) {
            //        if (calRes.flag == 1 && !bRe[1]) {
            //            var fy = cam.position.y;
            //            var opt = { fixY: fy };
            //            Fisp.mcAuxi.transObj(cam, "tx", -dx, { fixY: fy });
            //            Fisp.mcAuxi.transObj(cam, "tz", dy, { fixY: fy });
            //        }
            //        else if (calRes.flag == 2 && !bRe[2]) {
            //            Fisp.mcAuxi.transObj(cam, "tz", calRes.zoom);
            //            Fisp.mcAuxi.transObj(cam, "rx", calRes.pushY * 0.005);
            //            Fisp.mcAuxi.transObj(cam, "ry", calRes.spin);
            //        }
            //        else if (calRes.flag == 3 && !bRe[3]) {
            //        }
            //    }
            //}
            //mthis.resetPts(evt, 1);
        }

        onTouchEnd(evt) {
            //evt.preventDefault();
            this.resetPts(evt, 1);
        }

        onTouchCancel(evt) {
        }

        calMouse(evt) {
            var flag = (this.mptTs.flag > 0) ? this.mptTs.flag : 0;
            var calRes = { dx: (evt.clientX - this.mptTs.pt[flag].x), dy: (evt.clientY - this.mptTs.pt[flag].y), flag: this.mptTs.flag, ptTs: this.mptTs };
            return calRes;
        }

        calTouch(evt) {
            //var ptTs = { pt: [{ x: 0, y: 0, on: false }, { x: 0, y: 0, on: false }, { x: 0, y: 0, on: false }, { x: 0, y: 0, on: false }, { x: 0, y: 0, on: false }], flag: -1 };
            //var ptCs = { pt: [{ x: 0, y: 0, on: false }, { x: 0, y: 0, on: false }, { x: 0, y: 0, on: false }, { x: 0, y: 0, on: false }, { x: 0, y: 0, on: false }], flag: -1 };
            //var touch = event.touches;
            //ptTs.flag = touch.length;
            //for (var i = 0; i < touch.length; i++) {
            //    ptTs.pt[i].x = touch[i].clientX;
            //    ptTs.pt[i].y = touch[i].clientY;
            //    ptTs.pt[i].on = true;
            //}
            //var chang = event.changedTouches;
            //ptCs.flag = chang.length;
            //for (var i = 0; i < chang.length; i++) {
            //    ptCs.pt[i].x = chang[i].clientX;
            //    ptCs.pt[i].y = chang[i].clientY;
            //    ptCs.pt[i].on = true;
            //}
            ////
            //var calRes = new Object();
            //calRes.dx = 0;
            //calRes.dy = 0;
            //calRes.zoom = 0;
            //calRes.drift = 0;
            //calRes.pushX = 0;
            //calRes.pushY = 0;
            //calRes.spin = 0;
            //calRes.flag = ptTs.flag;
            //if (ptTs.flag > 0) {
            //    calRes.dx = ptTs.pt[0].x - mthis.mptTs.pt[0].x;
            //    calRes.dy = ptTs.pt[0].y - mthis.mptTs.pt[0].y;
            //}
            //if (ptTs.flag > 1) {
            //    var p0 = new Object();
            //    p0.x = mthis.mptTs.pt[0].x; p0.y = mthis.mptTs.pt[0].y;
            //    var p1 = new Object();
            //    p1.x = mthis.mptTs.pt[1].x; p1.y = mthis.mptTs.pt[1].y;
            //    var pA = new Object();
            //    pA.x = ptTs.pt[0].x; pA.y = ptTs.pt[0].y;
            //    var pB = new Object();
            //    pB.x = ptTs.pt[1].x; pB.y = ptTs.pt[1].y;
            //    //
            //    var p0c = new Object();
            //    p0c.x = (p1.x + p0.x) * 0.5;
            //    p0c.y = (p1.y + p0.y) * 0.5;
            //    var pAc = new Object();
            //    pAc.x = (pB.x + pA.x) * 0.5;
            //    pAc.y = (pB.y + pA.y) * 0.5;
            //    //
            //    var p01 = new Object();
            //    p01.x = p1.x - p0.x;
            //    p01.y = p1.y - p0.y;
            //    var pAB = new Object();
            //    pAB.x = pB.x - pA.x;
            //    pAB.y = pB.y - pA.y;
            //    var l01 = Math.sqrt(p01.x * p01.x + p01.y * p01.y);
            //    var lAB = Math.sqrt(pAB.x * pAB.x + pAB.y * pAB.y);
            //    //
            //    calRes.zoom = Math.sqrt(Math.pow(pB.x - pA.x, 2) + Math.pow(pB.y - pA.y, 2)) - Math.sqrt(Math.pow(p1.x - p0.x, 2) + Math.pow(p1.y - p0.y, 2));
            //    calRes.drift = Math.sqrt(Math.pow(pAc.x - p0c.x, 2) + Math.pow(pAc.y - p0c.y, 2));
            //    if (Math.abs(pA.x - p0.x) < 5 && Math.abs(pB.x - p1.x) < 5 && Math.abs(p1.x - p0.x) > 100) {
            //        calRes.pushY = Math.sqrt(Math.pow(pAc.x - p0c.x, 2) + Math.pow(pAc.y - p0c.y, 2)) * Math.sign(pAc.y - p0c.y);
            //    }
            //    if (Math.abs(pA.y - p0.y) < 5 && Math.abs(pB.y - p1.y) < 5 && Math.abs(p1.y - p0.y) > 100) {
            //        calRes.pushX = Math.sqrt(Math.pow(pAc.x - p0c.x, 2) + Math.pow(pAc.y - p0c.y, 2)) * Math.sign(pAc.x - p0c.x);
            //    }
            //    var si = 0;
            //    if (p01.x == 0) {
            //        if (p01.y > 0) { si = (pAB.x > 0) ? -1 : 1; }
            //        if (p01.y < 0) { si = (pAB.x < 0) ? -1 : 1; }
            //    }
            //    else if (pAB.x == 0) {
            //        if (pAB.y > 0) { si = (p01.x < 0) ? -1 : 1; }
            //        if (pAB.y < 0) { si = (pAB.x > 0) ? -1 : 1; }
            //    }
            //    else if (p01.y * pAB.y >= 0) { si = Math.sign(p01.y / p01.x - pAB.y / pAB.x); }
            //    else if ((p01.y >= 0 && pAB.y <= 0) || (p01.y <= 0 && pAB.y >= 0)) { si = -1; }
            //    else { si = 1; }
            //    calRes.spin = Math.acos((p01.x * pAB.x + p01.y * pAB.y) / (l01 * lAB)) * si;
            //}
            //if (ptTs.flag > 2) {
            //}
            //return calRes;
        }

        resetPts(evt, type, bMoving?) {
            var ptTs = this.mptTs;
            this.mptTs = { pt: [{ x: 0, y: 0, on: false }, { x: 0, y: 0, on: false }, { x: 0, y: 0, on: false }, { x: 0, y: 0, on: false }, { x: 0, y: 0, on: false }], flag: -1 };
            this.mptCs = { pt: [{ x: 0, y: 0, on: false }, { x: 0, y: 0, on: false }, { x: 0, y: 0, on: false }, { x: 0, y: 0, on: false }, { x: 0, y: 0, on: false }], flag: -1 };
            //if (0 == type && evt) {
            //    mthis.mptTs.pt[evt.button].x = evt.clientX;
            //    mthis.mptTs.pt[evt.button].y = evt.clientY;
            //    mthis.mptTs.pt[evt.button].on = true;
            //    mthis.mptTs.flag = evt.button;
            //    if (bMoving) {
            //        mthis.mptTs.pt[0].on = ptTs.pt[0].on;
            //        mthis.mptTs.pt[1].on = ptTs.pt[1].on;
            //        mthis.mptTs.pt[2].on = ptTs.pt[2].on;
            //        mthis.mptTs.pt[3].on = ptTs.pt[3].on;
            //        mthis.mptTs.pt[4].on = ptTs.pt[4].on;
            //    }
            //}
            //else if (1 == type && event) {
            //    var touch = event.touches;
            //    mthis.mptTs.flag = touch.length;
            //    for (var i = 0; i < touch.length; i++) {
            //        mthis.mptTs.pt[i].x = touch[i].clientX;
            //        mthis.mptTs.pt[i].y = touch[i].clientY;
            //        mthis.mptTs.pt[i].on = true;
            //    }
            //    var chang = event.changedTouches;
            //    mthis.mptCs.flag = chang.length;
            //    for (var i = 0; i < chang.length; i++) {
            //        mthis.mptCs.pt[i].x = chang[i].clientX;
            //        mthis.mptCs.pt[i].y = chang[i].clientY;
            //        mthis.mptCs.pt[i].on = true;
            //    }
            //}
        }

        lastState() {
            return this.mptTs;
        }

        onKeyDownFreeCam(evt) {
            //var cam = Fisp.mcCamera.camera();
            //var delta = cam.speed;
            //if (evt.keyCode == 87) {
            //    Fisp.mcAuxi.freeCamOp("tz", delta);
            //}
            //if (evt.keyCode == 83) {
            //    Fisp.mcAuxi.freeCamOp("tz", -delta);
            //}
            //if (evt.keyCode == 81) {
            //    Fisp.mcAuxi.freeCamOp("tx", -delta);
            //}
            //if (evt.keyCode == 69) {
            //    Fisp.mcAuxi.freeCamOp("tx", delta);
            //}
            //if (evt.keyCode == 65) {
            //    Fisp.mcAuxi.freeCamOp("ry", -delta * 0.05);
            //}
            //if (evt.keyCode == 68) {
            //    Fisp.mcAuxi.freeCamOp("ry", delta * 0.05);
            //}
        }

        onKeyDownFollowCam(evt) {
            ////var cam = Fisp.mcCamera.camera();
            //var delta = 0.1;//cam.speed;
            //if (evt.keyCode == 87) {
            //    Fisp.mcAuxi.avatorOp("tz", -delta);
            //}
            //if (evt.keyCode == 83) {
            //    Fisp.mcAuxi.avatorOp("tz", delta);
            //}
            //if (evt.keyCode == 81) {
            //    Fisp.mcAuxi.avatorOp("tx", delta * 0.5);
            //}
            //if (evt.keyCode == 69) {
            //    Fisp.mcAuxi.avatorOp("tx", -delta * 0.5);
            //}
            //if (evt.keyCode == 65) {
            //    Fisp.mcAuxi.avatorOp("ry", -delta * 0.5);
            //}
            //if (evt.keyCode == 68) {
            //    Fisp.mcAuxi.avatorOp("ry", delta * 0.5);
            //}
        }

        onKeyDownFlyCam(evt) {
            //var cam = Fisp.mcCamera.camera();
            //var delta = cam.speed;
            //if (evt.keyCode == 87) {
            //    Fisp.mcAuxi.freeCamOp("tz", delta);
            //}
            //if (evt.keyCode == 83) {
            //    Fisp.mcAuxi.freeCamOp("tz", -delta);
            //}
            //if (evt.keyCode == 81) {
            //    Fisp.mcAuxi.freeCamOp("tx", -delta);
            //}
            //if (evt.keyCode == 69) {
            //    Fisp.mcAuxi.freeCamOp("tx", delta);
            //}
            //if (evt.keyCode == 65) {
            //    Fisp.mcAuxi.freeCamOp("ry", -delta * 0.05);
            //}
            //if (evt.keyCode == 68) {
            //    Fisp.mcAuxi.freeCamOp("ry", delta * 0.05);
            //}
        }

        onResize(evt) {
            gRoot.mEngineImp.resize();
            gRoot.mFrame.onResize(evt);
        }

    }

}