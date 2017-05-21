namespace Fisp {
    export class UIMgr {
        canvasCss: any;
        canvas: HTMLCanvasElement;
        groups: Array<any>;
        guiVisible: boolean;
        GUIstyle: any;
        GUItheme: any;
        pixel: any;
        themeRoot: any;
        theme: any;
        head: any;
        html: any;
        header: any;
        id: any;
        //
        guiElements: any;
        convertPixelToPercent: boolean;
        //
        userData: any;

        constructor(canvas, css, options) {
            this.canvasCss = css;
            this.canvas = canvas;
            this.groups = [];
            this.guiVisible = true;
            this.GUIstyle = null;
            this.GUItheme = null;
            if (options) {
                this.pixel = options.pixel || true;
                this.themeRoot = options.themeRoot || "";
                this.theme = options.themeGUI || "default";
            } else {
                this.pixel = true;
                this.themeRoot = "";
                this.theme = "default";
            }
            this.head = document.head || document.getElementsByTagName('head')[0] || null;
            this.html = document.body || document.getElementsByTagName('body')[0];
            if (this.head == null) {
                this.header = document.createElement('head');
                this.head.appendChild(this.header);
            }
            this.addStyle(this.canvasCss, this.theme);
            //document.addEventListener('webkitfullscreenchange', function () { location.reload(); }, false);
            //document.addEventListener('mozfullscreenchange', function () { location.reload(); }, false);
            //document.addEventListener('fullscreenchange', function () { location.reload(); }, false);
            //document.addEventListener('MSFullscreenChange', function () { location.reload(); }, false);
            //
            this.guiElements = [];
            this.convertPixelToPercent = false;
            this.userData = new Object();
            this.userData.dlgList = [];
        }

        regUserDlg(dlg) {
            this.userData.dlgList.push(dlg);
        }

        findUserDlg(dlgName) {
            var dlg = null;
            var cnt = this.userData.dlgList.length;
            for (var i = 0; i < cnt; i++) {
                if (dlgName == this.userData.dlgList[i].name()) {
                    dlg = this.userData.dlgList[i];
                    break;
                }
            }
            return dlg;
        }

        addGuiElements(elem) {
            this.guiElements.push(elem);
        }

        convertPixelToPercentWidth(pixel) {
            var screenWidth = window.innerWidth;
            var valueWidth = (pixel / screenWidth) * 100;
            return valueWidth;
        }

        convertPixelToPercentHeight(pixel) {
            var screenHeight = window.innerHeight;
            var valueHeight = (pixel / screenHeight) * 100;
            return valueHeight;
        }

        addStyle(css, theme) {
            // CSS
            if (this.GUIstyle) {
                this.head.removeChild(this.getElementById("styleGUI"));
                this.canvasCss = this.canvasCss + css;
            } else {
                this.canvasCss = this.canvasCss;
            }
            this.GUIstyle = document.createElement('style');
            this.GUIstyle.type = 'text/css';
            this.GUIstyle.media = 'screen';
            this.GUIstyle.id = "styleGUI";
            if (this.GUIstyle.styleSheet) {
                this.GUIstyle.styleSheet.cssText = this.canvasCss;
            } else {
                this.GUIstyle.appendChild(document.createTextNode(this.canvasCss));
            }
            this.head.appendChild(this.GUIstyle);

            //Theme
            if (this.GUItheme) {
                this.head.removeChild(this.getElementById("themeGUI"));
            }
            this.GUItheme = document.createElement('link');
            this.GUItheme.type = 'text/css';
            this.GUItheme.rel = 'stylesheet';
            this.GUItheme.media = 'screen';
            this.GUItheme.id = "themeGUI";
            this.GUItheme.href = this.themeRoot + "themesGUI/" + theme + ".css";
            this.head.appendChild(this.GUItheme);
        }

        fadeOut(el) {
            if (el) {
                el.style.opacity = 1;
                (function fade_moin() {
                    if ((el.style.opacity -= 0.1) < 0.1) {
                        el.style.display = "none";
                        el.style.opacity = 0;
                    } else if (el.style.opacity > 0) {
                        requestAnimationFrame(fade_moin);
                    }
                })();
            }
        }

        fadeIn(el) {
            if (el) {
                el.style.opacity = 0;
                el.style.display = "block";
                (function fade_plus() {
                    var val = parseFloat(el.style.opacity);
                    if (!((val += 0.1) > 0.9)) {
                        el.style.opacity = 1;
                        requestAnimationFrame(fade_plus);
                    }
                })();
            }
        }

        getElementById(id) {
            return document.getElementById(id);
        }

        getCanvasOrigine() {
            var offsets = this.canvas.getBoundingClientRect(),
                offsetsTop = offsets.top || 0,
                offsetsLeft = offsets.left || 0;
            return { top: offsetsTop, left: offsetsLeft };
        }

        getCanvasSize() {
            var offsets = this.canvas.getBoundingClientRect(),
                offsetsWidth = offsets.width || 0,
                offsetsHeight = offsets.height || 0;
            return { width: offsetsWidth, height: offsetsHeight };
        }

        dispose() {
            var that = this;
            this.guiElements.forEach(function (e) {
                if (that.getElementById(e.id)) {
                    that.html.removeChild(that.getElementById(e.id));
                }
            });
            return;
        }

        setVisible(bool, fade) {
            var display;
            var that = this;
            if (fade == undefined) fade = true;
            var element = this.getElementById(this.id);
            if (bool == true) {
                display = "block";
                this.guiVisible = true;
                if (fade == true) { this.fadeIn(element); }
            } else {
                display = "none";
                this.guiVisible = false;
                if (fade == true) { this.fadeOut(element); }
            }
            if (fade == false) {
                this.guiElements.forEach(function (e) {
                    that.getElementById(e.id).style.display = display;
                });
            }
        }

        isVisible() {
            return this.guiVisible;
        }

        heightThreshold(): number {
            return 500;
        }

        widthThreshold(): number {
            return 500;
        }
    }

    //
    export class UIDrag {
        static currentElement: any = null;
        static fairlyHighZIndex: any = '10';

        constructor() {
            UIDrag.currentElement = null;
            UIDrag.fairlyHighZIndex = '10';
        }

        static addEventListener(element, eventName, handler) {
            if (element.addEventListener) {
                element.addEventListener(eventName, handler, false);
            } else if (element.attachEvent) {
                element.attachEvent('on' + eventName, handler);
            } else {
                element['on' + eventName] = handler;
            }
        }

        static removeEventListener(element, eventName, handler) {
            if (element.removeEventListener) {
                element.removeEventListener(eventName, handler, false);
            } else if (element.detachEvent) {
                element.detachEvent('on' + eventName, handler);
            } else {
                element['on' + eventName] = null;
            }
        }

        static draggable(evt, element, handle) {
            handle = handle || element;
            UIDrag.currentElement = element || handle;
            UIDrag.setPositionType(element);
            UIDrag.setDraggableListeners(element);
            UIDrag.addEventListener(handle, 'mousedown', function (event) {
                UIDrag.startDragging(event, element);
            });
        }

        static setPositionType(element) {
            element.style.position = 'absolute';
        }

        static setDraggableListeners(element) {
            element.draggableListeners = {
                start: [],
                drag: [],
                stop: []
            };
            element.whenDragStarts = UIDrag.addListener(element, 'start');
            element.whenDragging = UIDrag.addListener(element, 'drag');
            element.whenDragStops = UIDrag.addListener(element, 'stop');
        }

        static startDragging(event, element) {
            UIDrag.currentElement && UIDrag.sendToBack(UIDrag.currentElement);
            UIDrag.currentElement = UIDrag.bringToFront(element);
            var initialPosition = UIDrag.getInitialPosition(UIDrag.currentElement);
            UIDrag.currentElement.style.left = UIDrag.inPixels(initialPosition.left);
            UIDrag.currentElement.style.top = UIDrag.inPixels(initialPosition.top);
            UIDrag.currentElement.lastXPosition = event.clientX;
            UIDrag.currentElement.lastYPosition = event.clientY;
            var okToGoOn = UIDrag.triggerEvent('start', { x: initialPosition.left, y: initialPosition.top, mouseEvent: event });
            if (!okToGoOn) { return; }
            UIDrag.addDocumentListeners();
        }

        static addListener(element, type) {
            return function (listener) {
                element.draggableListeners[type].push(listener);
            };
        }

        static triggerEvent(type, args) {
            var result = true;
            var listeners = UIDrag.currentElement.draggableListeners[type];
            for (var i = listeners.length - 1; i >= 0; i--) {
                if (listeners[i](args) === false) { result = false; }
            };
            return result;
        }

        static sendToBack(element) {
            var decreasedZIndex = UIDrag.fairlyHighZIndex - 1;
            element.style['z-index'] = decreasedZIndex;
            element.style['zIndex'] = decreasedZIndex;
        }

        static bringToFront(element) {
            element.style['z-index'] = UIDrag.fairlyHighZIndex;
            element.style['zIndex'] = UIDrag.fairlyHighZIndex;
            return element;
        }

        static addDocumentListeners() {
            UIDrag.addEventListener(document, 'selectstart', UIDrag.cancelDocumentSelection);
            UIDrag.addEventListener(document, 'mousemove', UIDrag.repositionElement);
            UIDrag.addEventListener(document, 'mouseup', UIDrag.removeDocumentListeners);
            UIDrag.addEventListener(document, "touchstart", UIDrag.cancelDocumentSelection);
            UIDrag.addEventListener(document, "touchmove", UIDrag.repositionElement);
            UIDrag.addEventListener(document, "touchend", UIDrag.removeDocumentListeners);
            UIDrag.addEventListener(document, "touchcancel", UIDrag.removeDocumentListeners);
        }

        static getInitialPosition(element) {
            var boundingClientRect = element.getBoundingClientRect();
            return {
                top: boundingClientRect.top,
                left: boundingClientRect.left
            };
        }

        static inPixels(value) {
            return value + 'px';
        }

        static cancelDocumentSelection(event) {
            event.preventDefault && event.preventDefault();
            event.stopPropagation && event.stopPropagation();
            event.returnValue = false;
            return false;
        }

        static repositionElement(event) {
            event.preventDefault && event.preventDefault();
            event.returnValue = false;
            var style = UIDrag.currentElement.style;
            var elementXPosition = parseInt(style.left, 10);
            var elementYPosition = parseInt(style.top, 10);

            var elementNewXPosition = elementXPosition + (event.clientX - UIDrag.currentElement.lastXPosition);
            var elementNewYPosition = elementYPosition + (event.clientY - UIDrag.currentElement.lastYPosition);

            style.left = UIDrag.inPixels(elementNewXPosition);
            style.top = UIDrag.inPixels(elementNewYPosition);

            UIDrag.currentElement.lastXPosition = event.clientX;
            UIDrag.currentElement.lastYPosition = event.clientY;

            UIDrag.triggerEvent('drag', { x: elementNewXPosition, y: elementNewYPosition, mouseEvent: event });
        }

        static removeDocumentListeners(event) {
            UIDrag.removeEventListener(document, 'selectstart', UIDrag.cancelDocumentSelection);
            UIDrag.removeEventListener(document, 'mousemove', UIDrag.repositionElement);
            UIDrag.removeEventListener(document, 'mouseup', UIDrag.removeDocumentListeners);
            UIDrag.removeEventListener(document, "touchstart", UIDrag.cancelDocumentSelection);
            UIDrag.removeEventListener(document, "touchmove", UIDrag.repositionElement);
            UIDrag.removeEventListener(document, "touchend", UIDrag.removeDocumentListeners);
            UIDrag.removeEventListener(document, "touchcancel", UIDrag.removeDocumentListeners);

            var left = parseInt(UIDrag.currentElement.style.left, 10);
            var top = parseInt(UIDrag.currentElement.style.top, 10);
            UIDrag.triggerEvent('stop', { x: left, y: top, mouseEvent: event });
        }

        //
        static drag(evt, dlg, ele) {
            UIDrag.avoidSelect(evt);
            UIDrag.currentElement = dlg || ele;
            UIDrag.repositionElement(evt);
       }

        static avoidSelect(evt) {
            evt.preventDefault();
            window.getSelection ? window.getSelection().removeAllRanges() : document.getSelection().empty();
        }

    }

    //
    export class UIWindow extends UIMgr {
        windowPosition: any;
        windowSize: any;
        colorWindow: any;
        imageWindow: any;
        colorContent: any;
        imageContent: any;
        buttonClose: any;
        overflow: any;
        borderWindow: any;
        borderTitle: any;
        heightTitle: any;
        fontSize: any;
        radiusWindow: any;
        colorTitle: any;
        imageTitle: any;
        textAlign: any;
        colorTextTitle: any;
        title: any;
        draggable: any;
        zIndex: any;
        windowVisible: any;

        constructor(id, options, guiMgr: UIMgr) {
            super(guiMgr.canvas, guiMgr.canvasCss, options);
            this.id = id;
            this.html = document.body || document.getElementsByTagName('body')[0];
            this.windowPosition = { x: options.x, y: options.y };
            this.windowSize = { width: options.w, height: options.h };
            this.colorWindow = options.backgroundColor || null;
            this.imageWindow = options.backgroundImage || null;
            this.colorContent = options.colorContent || null;
            this.imageContent = options.imageContent;
            this.buttonClose = typeof options.closeButton;
            this.overflow = options.overflow || "auto";
            this.borderWindow = options.borderWindow || null;
            this.borderTitle = options.borderTitle || null;
            this.heightTitle = options.heightTitle || 30;
            this.fontSize = options.titleFontSize || 24;
            this.radiusWindow = options.radiusWindow || 8;
            this.colorTitle = options.colorTitle || "rgba(0, 0, 0, 0.4)";
            this.imageTitle = options.imageTitle || null;
            this.textAlign = options.titleTextAlign || "center";
            this.colorTextTitle = options.titleColor || null;
            this.title = options.textTitle || "Title";
            if (options.draggable == true || options.draggable == undefined) {
                this.draggable = true;
            } else {
                this.draggable = false;
            }
            this.zIndex = options.zIndex || 0;
            this.windowVisible = false;

            this.addElement(null, null);
        }

        addElement(append, element) {
            var signe = "";
            if (this.pixel) { signe = "px"; }
            else { signe = "%"; }
            var window = document.createElement("div");
            window.style.position = "absolute";
            window.style.width = this.windowSize.width + "px";
            window.style.height = this.windowSize.height + "px";
            if (this.convertPixelToPercent == true) {
                window.style.top = this.convertPixelToPercentHeight(this.windowPosition.y + this.getCanvasOrigine().top) + "%";
                window.style.left = this.convertPixelToPercentWidth(this.windowPosition.x + this.getCanvasOrigine().left) + "%";
            } else {
                window.style.top = (this.windowPosition.y + this.getCanvasOrigine().top) + signe;
                window.style.left = (this.windowPosition.x + this.getCanvasOrigine().left) + signe;
            }
            window.style.borderRadius = this.radiusWindow + "px";
            window.id = this.id;
            //window.tagName = this.id;
            window.className = "GUIWindow";
            window.draggable = this.draggable;
            window.style.zIndex = this.zIndex || 0;
            window.style.backgroundColor = this.colorWindow;
            window.style.backgroundImage = "url(" + this.imageWindow + ")";
            window.style.border = this.borderWindow;
            window.style.wordWrap = "break-word";
            window.style.display = "none";

            var titreWindow = document.createElement("div");
            titreWindow.className = "titleWindoWGUI";
            titreWindow.id = this.id + "_titre";
            titreWindow.draggable = this.draggable;
            titreWindow.style.width = this.windowSize.width + "px";
            titreWindow.style.height = this.heightTitle + "px";
            titreWindow.style.textAlign = this.textAlign;
            titreWindow.style.fontSize = this.fontSize + "px";
            titreWindow.style.borderRadius = this.radiusWindow + "px " + this.radiusWindow + "px 0 0";
            titreWindow.style.backgroundColor = this.colorTitle;
            titreWindow.style.backgroundImage = "url(" + this.imageTitle + ")";
            titreWindow.style.borderBottom = this.borderTitle;
            if (this.draggable == true) {
                UIDrag.draggable(null, window, titreWindow);
                //window.ondragstart = function (evt) { UIDrag.draggable(evt, window, window); }
                titreWindow.ondragstart = function (evt) { UIDrag.draggable(evt, window, titreWindow); }
                titreWindow.style.cursor = "move";
            }
            titreWindow.innerHTML = this.title;
            titreWindow.style.zIndex = this.zIndex + 1;
            titreWindow.style.color = this.colorTextTitle;
            titreWindow.style.wordWrap = "break-word";

            var that = this;
            if (this.buttonClose == true || this.buttonClose == "undefined") {
                var close = document.createElement("button");
                close.innerHTML = "X";
                close.id = this.id + "_button";
                close.style.position = "absolute";
                close.style.borderRadius = "12px";
                close.style.left = this.windowSize.width - 12 + "px";
                close.style.marginTop = "-12px";
                close.style.width = "24px";
                close.style.height = "24px";
                //close.style.zIndex = 10000;
                close.style.zIndex = "10000";
                close.onclick = function () { that.getElementById(that.id).style.display = "none"; that.windowVisible = false; };
            }

            var contentWindow = document.createElement("div");
            contentWindow.id = this.id + "_content";
            contentWindow.style.width = this.windowSize.width + "px";
            contentWindow.style.height = this.windowSize.height - 38 + "px";
            contentWindow.style.overflow = this.overflow;
            contentWindow.style.wordBreak = "keep-all";
            contentWindow.style.marginTop = "0px";
            contentWindow.style.paddingTop = "5px";
            contentWindow.style.borderRadius = "8px";
            contentWindow.style.backgroundColor = this.colorContent;
            contentWindow.style.backgroundImage = "url(" + this.imageContent + ")";
            contentWindow.style.zIndex = this.zIndex + 2;

            this.html.appendChild(window);
            this.getElementById(this.id).appendChild(titreWindow);
            if (this.buttonClose == true || this.buttonClose == "undefined") {
                this.getElementById(this.id + "_titre").appendChild(close);
            }
            this.getElementById(this.id).appendChild(contentWindow);

            this.addGuiElements(window);
        };

        titleWnd(newTitleText?: string): HTMLElement {
            var ele = this.getElementById(this.id + "_titre");
            if (ele && newTitleText)
                ele.innerHTML = newTitleText;
            return ele;
        }

        add(element) {
            var contentForm = this.getElementById(this.id + "_content");
            contentForm.style.zIndex = this.zIndex + 1;
            element.addElement(false, contentForm);
        };

        find(id): HTMLElement {
            var ele = this.getElementById(id);
            return ele;
        }

        updateText(id: string, newText: string) {
            var ele = this.getElementById(id);
            if (ele)
                ele.innerHTML = newText;
        }

        del(id: string): HTMLElement {
            var ele = this.getElementById(id);
            if (ele) {
                ele.parentElement.removeChild(ele);
            }
            return ele;
        }

        dispose() {
            return this.html.removeChild(this.getElementById(this.id));
        };

        setVisible(bool, fade = false) {
            var display;
            if (fade == undefined) fade = true;
            var element = this.getElementById(this.id);
            if (bool == true) {
                display = "block";
                this.windowVisible = true;
                if (fade == true) { this.fadeIn(element); }
            } else {
                display = "none";
                this.windowVisible = false;
                if (fade == true) { this.fadeOut(element); }
            }
            if (fade == false) { element.style.display = display; }
        };

        isVisible() {
            return this.windowVisible;
        };

        resize(id, w, h, x?, y?) {
            x = x || -1;
            y = y || -1;
            var ele: HTMLElement = this.getElementById(id);
            if (!ele)
                return;
            if(x >= 0)
                ele.style.left = x + 'px';
            if(y >= 0)
                ele.style.top = y + 'px';
            if (w >= 0) {
                ele.style.width = w + 'px';
            }
            if (h >= 0) {
                ele.style.height = h + 'px';
            }
        }
    }

    //
    export class UIPanel extends UIMgr {
        divPosition: any;
        divSize: any;
        divVisible: any;
        overflow: any;
        borderRadiusDiv: any;
        imageDiv: any;
        colorDiv: any;
        borderDiv: any;
        position: any;
        zIndex: any;

        constructor(id, options, guiMgr: UIMgr, callback, append) {
            super(guiMgr.canvas, guiMgr.canvasCss, options);
            if (append == null || append == undefined) { append = true; }

            this.id = id;
            this.html = document.body || document.getElementsByTagName('body')[0];
            this.divPosition = { x: options.x, y: options.y };
            this.divSize = { width: options.w, height: options.h };
            this.divVisible = false;
            this.overflow = options.overflow || "auto";
            this.borderRadiusDiv = options.borderRadiusPanel || "10px";
            this.imageDiv = options.backgroundImage || null;
            this.colorDiv = options.backgroundColor || null;
            this.borderDiv = options.borderPanel || null;
            this.position = options.position || "absolute";
            this.zIndex = options.zIndex || 1;

            if (append == true) {
                this.addElement(append, null);
            }
        }

        addElement(append, element) {
            var signe = "";
            if (this.pixel) { signe = "px"; }
            else { signe = "%"; }
            var div = document.createElement("div");
            if (this.divSize.width > 0 || this.divSize.height > 0) {
                div.style.width = this.divSize.width + "px";
                div.style.height = this.divSize.height + "px";
            }
            if (this.convertPixelToPercent == true) {
                if (append == true) {
                    if (this.divPosition.x > 0) {
                        div.style.left = this.convertPixelToPercentWidth(this.divPosition.x + this.getCanvasOrigine().left) + "%";
                    }
                    if (this.divPosition.y > 0) {
                        div.style.top = this.convertPixelToPercentHeight(this.divPosition.y + this.getCanvasOrigine().top) + "%";
                    }
                } else {
                    if (this.divPosition.x > 0) {
                        div.style.marginLeft = this.convertPixelToPercentWidth(this.divPosition.x) + "%";
                    }
                    if (this.divPosition.y > 0) {
                        div.style.marginTop = this.convertPixelToPercentHeight(this.divPosition.y) + "%";
                    }
                }
            } else {
                if (append == true) {
                    if (this.divPosition.x > 0) {
                        div.style.left = (this.divPosition.x + this.getCanvasOrigine().left) + signe;
                    }
                    if (this.divPosition.y > 0) {
                        div.style.top = (this.divPosition.y + this.getCanvasOrigine().top) + signe;
                    }
                } else {
                    if (this.divPosition.x > 0) {
                        div.style.marginLeft = this.divPosition.x + signe;
                    }
                    if (this.divPosition.y > 0) {
                        div.style.marginTop = this.divPosition.y + signe;
                    }
                }
            }
            div.id = this.id;
            //div.tagName = this.id;
            div.className = "GUIPanel";
            div.style.position = this.position;
            div.style.overflow = this.overflow;
            div.style.zIndex = this.zIndex;
            div.style.backgroundImage = "url(" + this.imageDiv + ")";
            div.style.backgroundColor = this.colorDiv;
            div.style.borderRadius = this.borderRadiusDiv;
            div.style.border = this.borderDiv;
            div.style.display = "none";

            if (append == true) {
                this.html.appendChild(div);
            } else {
                element.appendChild(div);
            }
            this.addGuiElements(div);
        }

        add(element) {
            var contentPanel = this.getElementById(this.id);
            contentPanel.style.zIndex = this.zIndex + 1;
            element.addElement(false, contentPanel);
        }

        del(id) {
            var ele = this.getElementById(id);
            alert("ele: " + id + ", " + ele);
            return this.html.removeChild(this.getElementById(id));
        }

        find(id): HTMLElement {
            var ele = this.getElementById(id);
            return ele;
        }

        dispose() {
            return this.html.removeChild(this.getElementById(this.id));
        }

        setVisible(bool, fade = false) {
            var display;
            if (fade == undefined) fade = true;
            var element = this.getElementById(this.id);
            if (bool == true) {
                display = "block";
                this.divVisible = true;
                if (fade == true) { this.fadeIn(element); }
            } else {
                display = "none";
                this.divVisible = false;
                if (fade == true) { this.fadeOut(element); }
            }
            if (fade == false) { element.style.display = display; }
        }

        isVisible() {
            return this.divVisible;
        }
    }

    //
    export class UIDialog extends UIMgr{
        dialogSize: any;
        dialogPosition: any;
        overflow: any;
        borderDialog: any;
        colorDialog: any;
        imageDialog: any;
        buttonDialog: any;
        imageButtonDialog: any;
        urlImage: any;
        callback: any;
        radius: any;
        zIndex: any;
        dialogVisible: any;
        
        constructor(id, options, guiMgr: UIMgr, callback, append) {
            super(guiMgr.canvas, guiMgr.canvasCss, options);
            if (append == null || append == undefined) { append = true; }

            this.id = id;
            this.html = document.body || document.getElementsByTagName('body')[0];
            this.dialogSize = { width: options.w, height: options.h };
            this.dialogPosition = { x: options.x, y: options.y };
            this.overflow = options.overflow || "auto";
            this.borderDialog = options.border || null;
            this.colorDialog = options.backgroundColor || null;
            this.imageDialog = options.backgroundImage || null;
            this.buttonDialog = options.closeDialog || "true";
            this.imageButtonDialog = options.imageButtonDialog || "false";
            this.urlImage = options.urlImage || null;
            this.callback = callback || null;
            this.radius = options.radius || 8;
            this.zIndex = options.zIndex || 0;
            this.dialogVisible = false;

            if (append == true) {
                this.addElement(append, null);
            }
        }

        addElement(append, element) {
            var signe = "";
            if (this.pixel) { signe = "px"; }
            else { signe = "%"; }
            var dialog = document.createElement("div");
            dialog.style.width = this.dialogSize.width + "px";
            dialog.style.height = this.dialogSize.height + "px";
            if (this.convertPixelToPercent == true) {
                dialog.style.top = this.convertPixelToPercentHeight(this.dialogPosition.y + this.getCanvasOrigine().top) + "%";
                dialog.style.left = this.convertPixelToPercentWidth(this.dialogPosition.x + this.getCanvasOrigine().left) + "%";
            } else {
                dialog.style.top = (this.dialogPosition.y + this.getCanvasOrigine().top) + signe;
                dialog.style.left = (this.dialogPosition.x + this.getCanvasOrigine().left) + signe;
            }
            dialog.style.position = "absolute";
            dialog.id = this.id;
            //dialog.tagName = this.id;
            dialog.className = "GUIDialog";
            dialog.style.zIndex = this.zIndex;
            dialog.style.background = this.colorDialog;
            dialog.style.borderRadius = this.radius + "px";
            dialog.style.backgroundImage = "url(" + this.imageDialog + ")";
            dialog.style.border = this.borderDialog;
            dialog.style.display = "none";
            dialog.style.overflow = this.overflow;
            var eventButton = null;

            if (append == true) {
                this.html.appendChild(dialog);
            } else {
                element.appendChild(dialog);
            }

            if (this.buttonDialog == "true") {
                eventButton = document.createElement("button");
                eventButton.innerHTML = "X";
                eventButton.id = this.id + "_button";
                eventButton.style.position = "absolute";
                eventButton.style.borderRadius = "12px";
                eventButton.style.border = "2px solid black";
                eventButton.style.left = this.dialogSize.width - 12 + signe;
                eventButton.style.marginTop = "-12px";
                eventButton.style.width = "25px";
                eventButton.style.height = "25px";
                eventButton.style.zIndex = 10000;
                eventButton.onclick = function () { document.body.removeChild(dialog); };
                this.getElementById(this.id).appendChild(eventButton);
            } else if (this.imageButtonDialog == "true") {
                var that = this;
                this.getSizeImage(this.urlImage, function (result) {
                    var sizeImageW = result.w;
                    var sizeImageH = result.h;
                    eventButton = document.createElement("img");
                    eventButton.src = that.urlImage;
                    eventButton.id = that.id + "_button";
                    eventButton.style.position = "absolute";
                    eventButton.style.left = that.dialogSize.width - (sizeImageW / 2) + signe;
                    eventButton.style.marginTop = "-" + (sizeImageH / 2) + signe;
                    eventButton.style.width = sizeImageW + signe;
                    eventButton.style.height = sizeImageH + signe;
                    eventButton.style.cursor = "pointer";
                    eventButton.style.zIndex = 10000;
                    eventButton.onclick = that.callback;
                    that.getElementById(that.id).appendChild(eventButton);
                });
            } else if (this.buttonDialog == "false" && this.imageButtonDialog == "false" && this.callback) {
                dialog.onclick = this.callback;
                dialog.style.cursor = "pointer";
            }

            this.addGuiElements(dialog);
        }

        getSizeImage(URL, callback) {
            var image = new Image();
            image.src = URL;
            image.onload = function () {
                var result = { w: image.width, h: image.height };
                callback(result);
            };
        }

        add(element) {
            var contentDialog = this.getElementById(this.id);
            contentDialog.style.zIndex = this.zIndex + 1;
            element.style.zIndex + 2;
            element.addElement(false, contentDialog);
        }

        dispose() {
            return this.html.removeChild(this.getElementById(this.id));
        }

        setVisible(bool, fade) {
            var display;
            if (fade == undefined) fade = true;
            var element = this.getElementById(this.id);
            if (bool == true) {
                display = "block";
                this.dialogVisible = true;
                if (fade == true) { this.fadeIn(element); }
            } else {
                display = "none";
                this.dialogVisible = false;
                if (fade == true) { this.fadeOut(element); }
            }
            if (fade == false) { element.style.display = display; }
        }

        isVisible() {
            return this.dialogVisible;
        }
    }

    //
    export class UIButton extends UIMgr {
        buttonPosition: any;
        buttonSize: any;
        value: any;
        buttonVisible: any;
        onClickButton: any;
        imageButton: any;
        colorButton: any;
        borderRadiusButton: any;
        borderButton: any;
        colorText: any;
        zIndex: any;
        tabindex: any;

        constructor(id, options, guiMgr: UIMgr, callback, append) {
            super(guiMgr.canvas, guiMgr.canvasCss, options);
            if (append == null || append == undefined) { append = true; }

            this.id = id;
            this.html = document.body || document.getElementsByTagName('body')[0];
            this.buttonPosition = { x: options.x, y: options.y };
            this.buttonSize = { width: options.w, height: options.h };
            this.value = options.value || "";
            this.buttonVisible = true;
            this.onClickButton = callback || false;
            this.imageButton = options.backgroundImage || null;
            this.colorButton = options.backgroundColor || null;
            this.borderRadiusButton = options.borderRadiusButton || null;
            this.borderButton = options.borderButton || null;
            this.colorText = options.colorText || null;
            this.zIndex = options.zIndex || 1;
            this.tabindex = options.tabindex || 0;

            if (append == true) {
                this.addElement(append, null);
            }
        }

        addElement(append, element) {
            var signe = "";
            if (this.pixel) { signe = "px"; }
            else { signe = "%"; }
            var button = document.createElement("button");
            button.style.width = this.buttonSize.width + "px";
            button.style.height = this.buttonSize.height + "px";
            if (this.convertPixelToPercent == true) {
                if (append == true) {
                    button.style.top = this.convertPixelToPercentHeight(this.buttonPosition.y + this.getCanvasOrigine().top) + "%";
                    button.style.left = this.convertPixelToPercentWidth(this.buttonPosition.x + this.getCanvasOrigine().left) + "%";
                } else {
                    button.style.top = (this.buttonPosition.y) + "px";
                    button.style.left = (this.buttonPosition.x) + "px";
                }
            } else {
                if (append == true) {
                    button.style.top = (this.buttonPosition.y + this.getCanvasOrigine().top) + signe;
                    button.style.left = (this.buttonPosition.x + this.getCanvasOrigine().left) + signe;
                } else {
                    button.style.top = this.buttonPosition.y + signe;
                    button.style.left = this.buttonPosition.x + signe;
                }
            }
            button.innerHTML = this.value;
            button.style.position = "absolute";
            button.id = this.id;
            button.name = this.id;
            button.style.zIndex = this.zIndex;
            button.className = "GUIButton";
            button.tabIndex = this.tabindex;
            button.style.borderRadius = this.borderRadiusButton;
            if (this.imageButton != null) {
                button.style.backgroundImage = "url(" + this.imageButton + ")";
            } else {
                button.style.background = this.colorButton;
            }
            button.style.border = this.borderButton;
            button.style.color = this.colorText;
            button.onclick = this.onClickButton;

            if (append == true) {
                this.html.appendChild(button);
            } else {
                element.appendChild(button);
            }
            this.addGuiElements(button);
        }

        dispose() {
            return this.html.removeChild(this.getElementById(this.id));
        }

        setVisible(bool, fade) {
            var display;
            if (fade == undefined) fade = true;
            var element = this.getElementById(this.id);
            if (bool == true) {
                display = "block";
                this.buttonVisible = true;
                if (fade == true) { this.fadeIn(element); }
            } else {
                display = "none";
                this.buttonVisible = false;
                if (fade == true) { this.fadeOut(element); }
            }
            if (fade == false) { element.style.display = display; }
        }

        isVisible() {
            return this.buttonVisible;
        }

        resize(x, y, w?, h?) {
            var ele = this.getElementById(this.id);
            ele.style.left = x + 'px';
            ele.style.top = y + 'px';
            if(w)
                ele.style.width = w + 'px';
            if(h)
                ele.style.height = h + 'px';
        }
    }

    //
    export class UILabel extends UIMgr {
        labelPosition: any;
        labelSize: any;
        textLabel: any;
        textColor: string;
        textSize: number;
        zIndex: any;
        labelVisible: any;

        constructor(id, options, guiMgr: UIMgr, append) {
            super(guiMgr.canvas, guiMgr.canvasCss, options);
            if (append == null || append == undefined) { append = true; }

            this.id = id;
            this.html = document.body || document.getElementsByTagName('body')[0];
            this.labelPosition = { x: options.x, y: options.y };
            this.labelSize = { width: options.w, height: options.h };
            this.textLabel = options.text;
            this.textColor = options.color || 'rgba(0,0,0,1.0)';
            this.textSize = options.size || 32;
            this.zIndex = options.zIndex || 1;
            this.labelVisible = true;

            if (append == true) {
                this.addElement(append, null);
            }
        }

        addElement(append, element) {
            var signe = "";
            if (this.pixel) { signe = "px"; }
            else { signe = "%"; }
            var label = document.createElement("label");
            if (this.convertPixelToPercent == true) {
                if (append == true) {
                    label.style.top = this.convertPixelToPercentHeight(this.labelPosition.y + this.getCanvasOrigine().top) + "%";
                    label.style.left = this.convertPixelToPercentWidth(this.labelPosition.x + this.getCanvasOrigine().left) + "%";
                } else {
                    label.style.top = (this.labelPosition.y) + "px";
                    label.style.left = (this.labelPosition.x) + "px";
                }
            } else {
                if (append == true) {
                    label.style.top = (this.labelPosition.y + this.getCanvasOrigine().top) + signe;
                    label.style.left = (this.labelPosition.x + this.getCanvasOrigine().left) + signe;
                } else {
                    label.style.top = this.labelPosition.y + signe;
                    label.style.left = this.labelPosition.x + signe;
                }
            }
            label.style.position = "absolute";
            label.id = this.id;
            //label.tagName = this.id;
            label.className = "GUILabel";
            label.innerHTML = this.textLabel;
            label.style.zIndex = this.zIndex;
            label.style.color = this.textColor;
            label.style.fontSize = this.textSize + 'px';
            if (append == true) {
                this.html.appendChild(label);
            } else {
                element.appendChild(label);
            }
            this.addGuiElements(label);
        }

        dispose() {
            return this.html.removeChild(this.getElementById(this.id));
        }

        setVisible(bool, fade) {
            var display;
            if (fade == undefined) fade = true;
            var element = this.getElementById(this.id);
            if (bool == true) {
                display = "block";
                this.labelVisible = true;
                if (fade == true) { this.fadeIn(element); }
            } else {
                display = "none";
                this.labelVisible = false;
                if (fade == true) { this.fadeOut(element); }
            }
            if (fade == false) { element.style.display = display; }
        }

        isVisible() {
            return this.labelVisible;
        }
    }

    //
    export class UIText extends UIMgr {
        append: boolean;
        textPosition: any;
        color: any;
        background: any;
        texte: any;
        zIndex: any;
        bold: any;
        italic: any;
        position: any;
        centerVertical: any;
        centerHorizontal: any;
        inline: any;
        textVisible: boolean;
        textElement: any;
        font: any;
        static textSize: any;
        static police: any;

        constructor(id, options, guiMgr: UIMgr, append) {
            super(guiMgr.canvas, guiMgr.canvasCss, options);
            this.append = append;
            if (append == null || append == undefined) { this.append = true; }

            this.id = id;
            this.html = document.body || document.getElementsByTagName('body')[0];
            this.textPosition = { x: options.x, y: options.y };
            UIText.textSize = options.size || 30;
            this.color = options.color || null;
            this.background = options.background || null;
            UIText.police = options.police || null;
            this.texte = options.text || "";
            this.zIndex = options.zIndex || 0;
            this.bold = options.bold || null; // bold
            this.italic = options.italic || null; //italic
            this.position = options.position || "absolute";
            this.centerVertical = options.centerVertical || false;
            this.centerHorizontal = options.centerHorizontal || false;
            this.inline = options.inline || false;
            this.textVisible = true;
            this.textElement = null;
            this.font = null;

            if (this.append == true) {
                this.addElement(this.append, null);
            }
        }

        addElement(append, element) {
            var signe = "";
            if (this.pixel) { signe = "px"; }
            else { signe = "%"; }
            this.font = UIText.textSize + "px " + UIText.police;
            this.textElement = document.createElement("span");
            if (this.inline == false) {
                this.textElement.style.width = "auto";
            } else {
                this.textElement.style.width = UIText.getTextWidth(this.texte, this.font).w + "px";
            }
            this.textElement.style.height = UIText.getTextWidth(this.texte, this.font).h + "px";
            if (this.convertPixelToPercent == true) {
                if (append == true) {
                    this.textElement.style.top = this.convertPixelToPercentHeight(this.textPosition.y + this.getCanvasOrigine().top) + "%";
                    this.textElement.style.left = this.convertPixelToPercentWidth(this.textPosition.x + this.getCanvasOrigine().left) + "%";
                } else {
                    this.textElement.style.top = (this.textPosition.y) + "px";
                    this.textElement.style.left = (this.textPosition.x) + "px";
                }
            } else {
                if (append == true) {
                    this.textElement.style.top = (this.textPosition.y + this.getCanvasOrigine().top) + signe;
                    this.textElement.style.left = (this.textPosition.x + this.getCanvasOrigine().left) + signe;
                } else {
                    this.textElement.style.top = this.textPosition.y + signe;
                    this.textElement.style.left = this.textPosition.x + signe;
                }
            }
            this.textElement.style.display = "block";
            this.textElement.style.position = this.position;
            this.textElement.style.font = this.font;
            this.textElement.style.color = this.color;
            this.textElement.style.background = this.background;
            this.textElement.style.fontStyle = this.italic;
            this.textElement.style.fontWeight = this.bold;
            this.textElement.innerHTML = this.texte;
            this.textElement.id = this.id;
            this.textElement.name = this.id;
            this.textElement.className = "GUIText";
            this.textElement.style.zIndex = this.zIndex;

            if (append == true) {
                if (this.centerVertical == "true") {
                    var marginTop = ((this.getCanvasSize().height / 2) - (UIText.getTextWidth(this.texte, this.font).h / 2));
                    this.textElement.style.top = (marginTop + this.getCanvasOrigine().top) + signe;
                }
                if (this.centerHorizontal == "true") {
                    var marginTotal = (this.getCanvasSize().width - UIText.getTextWidth(this.texte, this.font).w);
                    var marginLeft = (marginTotal / 2);
                    this.textElement.style.left = (marginLeft + this.getCanvasOrigine().left) + signe;
                }
                this.html.appendChild(this.textElement);
            } else {
                if (this.centerVertical == "true") {
                    this.textElement.style.top = "calc(50% - " + (UIText.getTextWidth(this.texte, this.font).h / 2) + "px)";
                }
                if (this.centerHorizontal == "true") {
                    this.textElement.style.width = "100%";
                    this.textElement.style.textAlign = "center";
                }
                element.appendChild(this.textElement);
            }
            this.addGuiElements(this.textElement);
        }

        updateText(text) {
            var signe = "";
            if (this.pixel) { signe = "px"; }
            else { signe = "%"; }
            if (this.append == true) {
                this.textElement.style.width = UIText.getTextWidth(text, this.font).w + signe;
                this.textElement.style.height = UIText.getTextWidth(text, this.font).h + signe;
                this.textElement.style.top = (this.textPosition.y + this.getCanvasOrigine().top) + signe;
                this.textElement.style.left = (this.textPosition.x + this.getCanvasOrigine().left) + signe;
            } else {
                this.textElement.style.top = this.textPosition.y + signe;
                this.textElement.style.left = this.textPosition.x + signe;
            }
            if (this.centerVertical == "true") {
                var marginTop = ((this.getCanvasSize().height / 2) - (UIText.getTextWidth(text, this.font).h / 2));
                this.textElement.style.top = (marginTop + this.getCanvasOrigine().top) + signe;
            }
            if (this.centerHorizontal == "true") {
                var marginTotal = (this.getCanvasSize().width - UIText.getTextWidth(text, this.font).w);
                var marginLeft = (marginTotal / 2);
                this.textElement.style.left = (marginLeft + this.getCanvasOrigine().left) + signe;
            }
            this.textElement.innerHTML = text;
        }

        static getTextWidth(texte, font) {
            var tag = document.createElement("div");
            tag.style.position = "absolute";
            tag.style.left = "-999em";
            tag.style.display = "block";
            tag.style.whiteSpace = "nowrap";
            tag.style.font = font || this.textSize + "px " + this.police;
            tag.innerHTML = texte;
            document.body.appendChild(tag);
            var result = { w: tag.clientWidth + 10, h: tag.clientHeight };
            document.body.removeChild(tag);
            return result;
        }

        dispose() {
            return this.html.removeChild(this.getElementById(this.id));
        }

        setVisible(bool, fade) {
            var display;
            if (fade == undefined) fade = true;
            var element = this.getElementById(this.id);
            if (bool == true) {
                display = "block";
                this.textVisible = true;
                if (fade == true) { this.fadeIn(element); }
            } else {
                display = "none";
                this.textVisible = false;
                if (fade == true) { this.fadeOut(element); }
            }
            if (fade == false) { element.style.display = display; }
        }

        isVisible(): boolean {
            return this.textVisible;
        }

    }

    //
    export class UITexture extends UIMgr {
        imageUrl: any;
        textureClicked: any;
        imageSize: any;
        imagePosition: any;
        imageVisible: any;
        zIndex: any;

        constructor(id, imageUrl, options, guiMgr: UIMgr, callback, append) {
            super(guiMgr.canvas, guiMgr.canvasCss, options);
            if (append == null || append == undefined) { append = true; }

            this.id = id;
            this.imageUrl = imageUrl;
            this.textureClicked = callback || false;
            this.imageSize = { width: options.w, height: options.h };
            this.imagePosition = { x: options.x, y: options.y };
            this.imageVisible = true;
            this.zIndex = options.zIndex || 1;
            this.html = document.body || document.getElementsByTagName('body')[0];

            if (append == true) {
                this.addElement(append, null);
            }
        }

        addElement(append, element) {
            var signe = "";
            if (this.pixel) { signe = "px"; }
            else { signe = "%"; }
            var img = document.createElement("img");
            img.src = this.imageUrl;
            img.style.width = this.imageSize.width + "px";
            img.style.height = this.imageSize.height + "px";
            if (this.convertPixelToPercent == true) {
                if (append == true) {
                    img.style.top = this.convertPixelToPercentHeight(this.imagePosition.y + this.getCanvasOrigine().top) + "%";
                    img.style.left = this.convertPixelToPercentWidth(this.imagePosition.x + this.getCanvasOrigine().left) + "%";
                } else {
                    img.style.top = (this.imagePosition.y) + "px";
                    img.style.left = (this.imagePosition.x) + "px";
                }
            } else {
                if (append == true) {
                    img.style.top = (this.imagePosition.y + this.getCanvasOrigine().top) + signe;
                    img.style.left = (this.imagePosition.x + this.getCanvasOrigine().left) + signe;
                } else {
                    img.style.top = this.imagePosition.y + signe;
                    img.style.left = this.imagePosition.x + signe;
                }
            }
            img.style.position = "absolute";
            img.style.zIndex = this.zIndex;
            img.id = this.id;
            img.name = this.id;
            img.className = "GUITexture";
            if (this.textureClicked) {
                var that = this;
                img.addEventListener('click', that.textureClicked, false);
            }

            if (append == true) {
                this.html.appendChild(img);
            } else {
                element.appendChild(img);
            }
            this.addGuiElements(img);
        }

        dispose() {
            return this.html.removeChild(this.getElementById(this.id));
        }

        setVisible(bool, fade) {
            var display;
            if (fade == undefined) fade = true;
            var element = this.getElementById(this.id);
            if (bool == true) {
                display = "block";
                this.imageVisible = true;
                if (fade == true) { this.fadeIn(element); }
            } else {
                display = "none";
                this.imageVisible = false;
                if (fade == true) { this.fadeOut(element); }
            }
            if (fade == false) { element.style.display = display; }
        }

        isVisible(): boolean {
            return this.imageVisible;
        }

    }

    //
    export class UITextArea extends UIMgr {
        textareaPosition: any;
        textareaSize: any;
        value: any;
        size: number;
        readOnly: boolean;
        placeholder: any;
        background: any;
        color: any;
        zIndex: any;
        textareaVisible: any;
        onchangeTextarea: any;
        tabindex: any;
        append: any;

        constructor(id, options, guiMgr: UIMgr, callback, append) {
            super(guiMgr.canvas, guiMgr.canvasCss, options);
            if (append == null || append == undefined) { append = true; }

            this.id = id;
            this.html = document.body || document.getElementsByTagName('body')[0];
            this.textareaPosition = { x: options.x, y: options.y };
            this.textareaSize = { row: options.row, col: options.col };
            this.value = options.value || "";
            this.size = options.size || 24;
            this.readOnly = options.readOnly || false;
            this.placeholder = options.placeholder || "";
            this.background = options.background || null;
            this.color = options.color || null;
            this.zIndex = options.zIndex || 2;
            this.textareaVisible = true;
            this.onchangeTextarea = callback || "";
            this.tabindex = options.tabindex || 0;
            this.append = append;

            if (this.append == true) {
                this.addElement(this.append, null);
            }
        }

        addElement(append, element) {
            var signe = "";
            if (this.pixel) { signe = "px"; }
            else { signe = "%"; }
            var textarea = document.createElement("textarea");
            textarea.rows = this.textareaSize.row;
            textarea.cols = this.textareaSize.col;
            if (this.convertPixelToPercent == true) {
                if (append == true) {
                    textarea.style.top = this.convertPixelToPercentHeight(this.textareaPosition.y + this.getCanvasOrigine().top) + "%";
                    textarea.style.left = this.convertPixelToPercentWidth(this.textareaPosition.x + this.getCanvasOrigine().left) + "%";
                } else {
                    textarea.style.top = (this.textareaPosition.y) + "px";
                    textarea.style.left = (this.textareaPosition.x) + "ox";
                }
            } else {
                if (append == true) {
                    textarea.style.top = (this.textareaPosition.y + this.getCanvasOrigine().top) + signe;
                    textarea.style.left = (this.textareaPosition.x + this.getCanvasOrigine().left) + signe;
                } else {
                    textarea.style.top = this.textareaPosition.y + signe;
                    textarea.style.left = this.textareaPosition.x + signe;
                }
            }
            textarea.style.position = "absolute";
            textarea.style.display = "block";
            textarea.placeholder = this.placeholder;
            textarea.id = this.id;
            textarea.name = this.id;
            textarea.className = "GUITextarea";
            textarea.tabIndex = this.tabindex;
            textarea.value = this.value;
            textarea.nodeValue = this.value;
            textarea.innerHTML = this.value;
            textarea.style.fontSize = this.size + 'px';
            textarea.readOnly = this.readOnly;
            textarea.style.zIndex = this.zIndex;
            if (this.background != null) {
                textarea.style.background = this.background;
            }
            if (this.color != null) {
                textarea.style.color = this.color;
            }
            textarea.onchange = this.onchangeTextarea;

            if (append == true) {
                this.html.appendChild(textarea);
            } else {
                element.appendChild(textarea);
            }
            this.addGuiElements(textarea);
        }

        getValue(): string {
            var ele = this.getElementById(this.id);
            var val = (<any>ele).value || ele.nodeValue;
            val = val || '';
            return val;
        }

        setValue(val) {
            this.value = val;
            (<any>this.getElementById(this.id)).value = val;
            this.getElementById(this.id).nodeValue = val;
        }

        addLine(val: string) {
            var strVal = this.getValue();
            if (strVal.length > 0)
                strVal += '\n';
            strVal += val;
            this.setValue(strVal);
            //
            var top = this.getElementById(this.id).scrollHeight;
            this.getElementById(this.id).scrollTop = top;
        }

        dispose() {
            return this.html.removeChild(this.getElementById(this.id));
        }

        setVisible(bool, fade) {
            var display;
            if (fade == undefined) fade = true;
            var element = this.getElementById(this.id);
            if (bool == true) {
                display = "block";
                this.textareaVisible = true;
                if (fade == true) { this.fadeIn(element); }
            } else {
                display = "none";
                this.textareaVisible = false;
                if (fade == true) { this.fadeOut(element); }
            }
            if (fade == false) { element.style.display = display; }
        }

        isVisible(): boolean {
            return this.textareaVisible;
        }

    }

    //
    export class UITextEdit extends UIMgr {
        textfieldPosition: any;
        textfieldSize: any;
        value: any;
        background: any;
        border: any;
        color: any;
        placeholder: any;
        zIndex: any;
        textfieldVisible: any;
        onchangeTextfield: any;
        tabindex: any;
        type: any;

        constructor(id, options, uiMgr: UIMgr, callback, append) {
            super(uiMgr.canvas, uiMgr.canvasCss, options);
            if (append == null || append == undefined) { append = true; }

            this.id = id;
            this.html = document.body || document.getElementsByTagName('body')[0];
            this.textfieldPosition = { x: options.x, y: options.y };
            this.textfieldSize = { width: options.w, height: options.h };
            this.value = options.value || "";
            this.background = options.background || null;
            this.border = options.border || null;
            this.color = options.color || null;
            this.placeholder = options.placeholder || "";
            this.zIndex = options.zIndex || 2;
            this.textfieldVisible = true;
            this.onchangeTextfield = callback || "";
            this.tabindex = options.tabindex || 0;
            this.type = options.type || "text";

            if (append == true) {
                this.addElement(append, null);
            }
        }

        addElement(append, element) {
            var signe = "";
            if (this.pixel) { signe = "px"; }
            else { signe = "%"; }
            var textfield = document.createElement("input");
            textfield.type = this.type;
            textfield.style.width = this.textfieldSize.width + "px";
            textfield.style.height = this.textfieldSize.height + "px";
            if (this.convertPixelToPercent == true) {
                if (append == true) {
                    textfield.style.top = this.convertPixelToPercentHeight(this.textfieldPosition.y + this.getCanvasOrigine().top) + "%";
                    textfield.style.left = this.convertPixelToPercentWidth(this.textfieldPosition.x + this.getCanvasOrigine().left) + "%";
                } else {
                    textfield.style.top = (this.textfieldPosition.y) + "px";
                    textfield.style.left = (this.textfieldPosition.x) + "px";
                }
            } else {
                if (append == true) {
                    textfield.style.top = (this.textfieldPosition.y + this.getCanvasOrigine().top) + signe;
                    textfield.style.left = (this.textfieldPosition.x + this.getCanvasOrigine().left) + signe;
                } else {
                    textfield.style.top = this.textfieldPosition.y + signe;
                    textfield.style.left = this.textfieldPosition.x + signe;
                }
            }
            textfield.style.position = "absolute";
            textfield.style.display = "block";
            textfield.id = this.id;
            textfield.name = this.id;
            textfield.className = "GUITextfield";
            textfield.tabIndex = this.tabindex;
            //
            textfield.value = this.value;
            textfield.nodeValue = this.value;
            //
            textfield.placeholder = this.placeholder;
            textfield.style.zIndex = this.zIndex;
            if (this.background != null) {
                textfield.style.background = this.background;
            }
            textfield.style.border = this.border;
            if (this.color != null) {
                textfield.style.color = this.color;
            }
            textfield.onchange = this.onchangeTextfield;

            if (append == true) {
                this.html.appendChild(textfield);
            } else {
                element.appendChild(textfield);
            }
            this.addGuiElements(textfield);
        }

        getValue() {
            var ele = this.getElementById(this.id);
            //return (<any>ele).value || ele.nodeValue;
            var val = (<any>ele).value || ele.nodeValue;
            val = val || '';
            return val;
        }

        setValue(val) {
            this.value = val;
            (<any>this.getElementById(this.id)).value = val;
            //if (this.getElementById(this.id).nodeValue != null)
            //    this.getElementById(this.id).nodeValue = val;
            //if (this.getElementById(this.id).innerHTML != null)
            //    this.getElementById(this.id).innerHTML = val;
            //if (this.getElementById(this.id).innerText != null)
            //    this.getElementById(this.id).innerText = val;
        }

        dispose() {
            return this.html.removeChild(this.getElementById(this.id));
        }

        setVisible(bool, fade) {
            var display;
            if (fade == undefined) fade = true;
            var element = this.getElementById(this.id);
            if (bool == true) {
                display = "block";
                this.textfieldVisible = true;
                if (fade == true) { this.fadeIn(element); }
            } else {
                display = "none";
                this.textfieldVisible = false;
                if (fade == true) { this.fadeOut(element); }
            }
            if (fade == false) { element.style.display = display; }
        }

        isVisible() {
            return this.textfieldVisible;
        }

    }

    //
    export class UICheckbox extends UIMgr {
        checkboxPosition: any;
        checkboxSize: any;
        zIndex: any;
        checkboxVisible: any;
        onClickCheckbox: any;
        tabindex: any;

        constructor(id, options, guiMgr: UIMgr, callback, append) {
            super(guiMgr.canvas, guiMgr.canvasCss, options);
            if (append == null || append == undefined) { append = true; }

            this.id = id;
            this.html = document.body || document.getElementsByTagName('body')[0];
            this.checkboxPosition = { x: options.x, y: options.y };
            this.checkboxSize = options.size || 1.0;
            this.zIndex = options.zIndex || 1.0;
            this.checkboxVisible = true;
            this.onClickCheckbox = callback || "";
            this.tabindex = options.tabindex || 0;

            if (append == true) {
                this.addElement(append, null);
            }
        }

        addElement(append, element) {
            var signe = "";
            if (this.pixel) { signe = "px"; }
            else { signe = "%"; }
            var checkbox = document.createElement("input");
            checkbox.type = "checkbox";
            checkbox.style.width = (this.checkboxSize * 16) + "px";
            checkbox.style.height = (this.checkboxSize * 16) + "px";
            if (this.convertPixelToPercent == true) {
                if (append == true) {
                    checkbox.style.top = this.convertPixelToPercentHeight(this.checkboxPosition.y + this.getCanvasOrigine().top) + "%";
                    checkbox.style.left = this.convertPixelToPercentWidth(this.checkboxPosition.x + this.getCanvasOrigine().left) + "%";
                } else {
                    checkbox.style.top = (this.checkboxPosition.y) + "px";
                    checkbox.style.left = (this.checkboxPosition.x) + "px";
                }
            } else {
                if (append == true) {
                    checkbox.style.top = (this.checkboxPosition.y + this.getCanvasOrigine().top) + signe;
                    checkbox.style.left = (this.checkboxPosition.x + this.getCanvasOrigine().left) + signe;
                } else {
                    checkbox.style.top = this.checkboxPosition.y + signe;
                    checkbox.style.left = this.checkboxPosition.x + signe;
                }
            }
            checkbox.style.position = "absolute";
            checkbox.style.padding = "0px";
            checkbox.style.margin = "0px";
            checkbox.id = this.id;
            checkbox.name = this.id;
            checkbox.className = "GUICheckbox";
            checkbox.tabIndex = this.tabindex;
            checkbox.style.zIndex = this.zIndex;
            checkbox.onclick = this.onClickCheckbox;

            if (append == true) {
                this.html.appendChild(checkbox);
            } else {
                element.appendChild(checkbox);
            }
            this.addGuiElements(checkbox);
        }

        isChecked() {
            var ele: HTMLInputElement = <HTMLInputElement>(this.getElementById(this.id));
            return ele.checked;
        }

        setChecked(value) {
            value = (value && value == true) ? true : false;
            (<HTMLInputElement>(this.getElementById(this.id))).checked = value;
        }

        dispose() {
            return this.html.removeChild(this.getElementById(this.id));
        }

        setVisible(bool, fade) {
            var display;
            if (fade == undefined) fade = true;
            var element = this.getElementById(this.id);
            if (bool == true) {
                display = "block";
                this.checkboxVisible = true;
                if (fade == true) { this.fadeIn(element); }
            } else {
                display = "none";
                this.checkboxVisible = false;
                if (fade == true) { this.fadeOut(element); }
            }
            if (fade == false) { element.style.display = display; }
        }

        isVisible() {
            return this.checkboxVisible;
        }

    }

    //
    export class UIRadiobox extends UIMgr {
        name: any;
        radioPosition: any;
        radioSize: any;
        zIndex: any;
        radioVisible: any;
        onClickRadio: any;
        tabindex: any;

        constructor(id, options, guiMgr: UIMgr, callback, append) {
            super(guiMgr.canvas, guiMgr.canvasCss, options);
            if (append == null || append == undefined) { append = true; }

            this.id = id;
            this.name = options.name || "NameRadio" + id;
            this.html = document.body || document.getElementsByTagName('body')[0];
            this.radioPosition = { x: options.x, y: options.y };
            this.radioSize = options.size || 1.0;
            this.zIndex = options.zIndex || 1;
            this.radioVisible = true;
            this.onClickRadio = callback || false;
            this.tabindex = options.tabindex || 0;

            if (append == true) {
                this.addElement(append, null);
            }
        }

        addElement(append, element) {
            var signe = "";
            if (this.pixel) { signe = "px"; }
            else { signe = "%"; }
            var radio = document.createElement("input");
            radio.type = "radio";
            radio.style.width = (this.radioSize * 16) + "px";
            radio.style.height = (this.radioSize * 16) + "px";
            if (this.convertPixelToPercent == true) {
                if (append == true) {
                    radio.style.top = this.convertPixelToPercentHeight(this.radioPosition.y + this.getCanvasOrigine().top) + "%";
                    radio.style.left = this.convertPixelToPercentWidth(this.radioPosition.x + this.getCanvasOrigine().left) + "%";
                } else {
                    radio.style.top = (this.radioPosition.y) + "px";
                    radio.style.left = (this.radioPosition.x) + "px";
                }
            } else {
                if (append == true) {
                    radio.style.top = (this.radioPosition.y + this.getCanvasOrigine().top) + signe;
                    radio.style.left = (this.radioPosition.x + this.getCanvasOrigine().left) + signe;
                } else {
                    radio.style.top = this.radioPosition.y + signe;
                    radio.style.left = this.radioPosition.x + signe;
                }
            }
            radio.style.position = "absolute";
            radio.style.padding = "0px";
            radio.style.margin = "0px";
            radio.id = this.id;
            radio.tabIndex = this.tabindex;
            radio.className = "GUIRadio";
            radio.name = this.name;
            radio.style.zIndex = this.zIndex;
            radio.onclick = this.onClickRadio;

            if (append == true) {
                this.html.appendChild(radio);
            } else {
                element.appendChild(radio);
            }

            this.addGuiElements(radio);
        }

        isChecked() {
            var ele: HTMLInputElement = <HTMLInputElement>(this.getElementById(this.id));
            return ele.checked;
        }

        setChecked(value) {
            value = (value && value == true) ? true : false;
            (<HTMLInputElement>(this.getElementById(this.id))).checked = value;
        }

        dispose() {
            return this.html.removeChild(this.getElementById(this.id));
        }

        setVisible(bool, fade) {
            var display;
            if (fade == undefined) fade = true;
            var element = this.getElementById(this.id);
            if (bool == true) {
                display = "block";
                this.radioVisible = true;
                if (fade == true) { this.fadeIn(element); }
            } else {
                display = "none";
                this.radioVisible = false;
                if (fade == true) { this.fadeOut(element); }
            }
            if (fade == false) { element.style.display = display; }
        }

        isVisible(): boolean {
            return this.radioVisible;
        }

    }

    //
    export class UIGroup extends UIMgr {
        groupPosition: any;
        guiManager: UIMgr;
        name: string;
        elementsGoup: Array<any>;
        groupVisible: boolean;

        constructor(name, options, guiMgr: UIMgr) {
            super(guiMgr.canvas, guiMgr.canvasCss, options);
            this.html = document.body || document.getElementsByTagName('body')[0];
            if (options) { this.groupPosition = { x: options.x, y: options.y }; }
            this.guiManager = guiMgr;
            this.name = name;
            this.elementsGoup = [];
            this.guiManager.groups.push(this);
            this.groupVisible = true;
        }

        add(guiElement) {
            this.elementsGoup.push(guiElement);
        }

        dispose() {
            var that = this;
            this.elementsGoup.forEach(function (e) {
                if (that.getElementById(e.id)) {
                    that.html.removeChild(that.getElementById(e.id));
                }
            });
            return;
        }

        setVisible(bool) {
            var display;
            var that = this;
            if (bool == true) {
                display = "block";
                this.groupVisible = true;
            } else {
                display = "none";
                this.groupVisible = false;
            }
            this.elementsGoup.forEach(function (e) {
                that.getElementById(e.id).style.display = display;
            });
            return;
        }

        isVisible(): boolean {
            return this.groupVisible;
        }

    }

    //
    export class UIColor extends UIMgr {
        colorPosition: any;
        colorSize: any;
        value: any;
        zIndex: any;
        colorVisible: any;
        onchangeColor: any;
        tabindex: any;

        constructor(id, options, guiMgr: UIMgr, callback, append) {
            super(guiMgr.canvas, guiMgr.canvasCss, options);
            if (append == null || append == undefined) { append = true; }

            this.id = id;
            this.html = document.body || document.getElementsByTagName('body')[0];
            this.colorPosition = { x: options.x, y: options.y };
            this.colorSize = { width: options.w, height: options.h };
            this.value = options.value || "#e30000";
            this.zIndex = options.zIndex || 1;
            this.colorVisible = true;
            this.onchangeColor = callback || "";
            this.tabindex = options.tabindex || 0;

            if (append == true) {
                this.addElement(append, null);
            }
        }

        addElement(append, element) {
            var signe = "";
            if (this.pixel) { signe = "px"; }
            else { signe = "%"; }
            var color = document.createElement("input");
            color.type = "color";
            color.value = this.value;
            color.className = "GUIColor";
            color.tabIndex = this.tabindex;
            color.style.width = this.colorSize.width + "px";
            color.style.height = this.colorSize.height + "px";
            if (this.convertPixelToPercent == true) {
                if (append == true) {
                    color.style.top = this.convertPixelToPercentHeight(this.colorPosition.y + this.getCanvasOrigine().top) + "%";
                    color.style.left = this.convertPixelToPercentWidth(this.colorPosition.x + this.getCanvasOrigine().left) + "%";
                } else {
                    color.style.top = (this.colorPosition.y) + "px";
                    color.style.left = (this.colorPosition.x) + "px";
                }
            } else {
                if (append == true) {
                    color.style.top = (this.colorPosition.y + this.getCanvasOrigine().top) + signe;
                    color.style.left = (this.colorPosition.x + this.getCanvasOrigine().left) + signe;
                } else {
                    color.style.top = this.colorPosition.y + signe;
                    color.style.left = this.colorPosition.x + signe;
                }
            }
            color.style.position = "absolute";
            color.id = this.id;
            color.name = this.id;
            color.style.zIndex = this.zIndex;
            color.onchange = this.onchangeColor;
            if ((navigator.userAgent.indexOf("MSIE") != -1) || (navigator.appName == "Netscape") || (!!document.compatMode == true) || navigator.appVersion.indexOf('Edge') > -1 || (navigator.appVersion.indexOf('Trident') == -1)) {
                //window.nativeColorGUI.init(this.id);
            }
            if (append == true) {
                this.html.appendChild(color);
            } else {
                element.appendChild(color);
            }
            this.addGuiElements(color);
        }

        getColor(rgb) {
            var hex = false;
            if (rgb == undefined) {
                rgb = true;
                hex = false;
            } else if (rgb == true) {
                rgb = true;
                hex = false;
            } else {
                rgb = false;
                hex = true;
            }
            var valueColor = null;
            var ele: HTMLInputElement = <HTMLInputElement>(this.getElementById(this.id));
            if (rgb == true) {
                valueColor = UIColor.hexToRgb(ele.value);
            } else if (hex == true) {
                valueColor = ele.value;
            }
            return valueColor;
        }

        dispose() {
            return this.html.removeChild(this.getElementById(this.id));
        }

        setVisible(bool, fade) {
            var display;
            if (fade == undefined) fade = true;
            var element = this.getElementById(this.id);
            if (bool == true) {
                display = "block";
                this.colorVisible = true;
                if (fade == true) { this.fadeIn(element); }
            } else {
                display = "none";
                this.colorVisible = false;
                if (fade == true) { this.fadeOut(element); }
            }
            if (fade == false) { element.style.display = display; }
        }

        isVisible(): boolean {
            return this.colorVisible;
        }

        static hexToR(h) { return parseInt((UIColor.cutHex(h)).substring(0, 2), 16) }
        static hexToG(h) { return parseInt((UIColor.cutHex(h)).substring(2, 4), 16) }
        static hexToB(h) { return parseInt((UIColor.cutHex(h)).substring(4, 6), 16) }
        static cutHex(h) { return (h.charAt(0) == "#") ? h.substring(1, 7) : h }
        static hexToRgb(hex) {
            var c_r = UIColor.hexToR(hex) / 255, c_g = UIColor.hexToG(hex) / 255, c_b = UIColor.hexToB(hex) / 255;
            return { r: c_r, g: c_g, b: c_b };
        }

    }

    //
    export class UIProgress extends UIMgr {
        progress: any;
        progressPosition: any;
        progressSize: any;
        min: any;
        max: any;
        value: any;
        border: any;
        background: any;
        backgroundValue: any;
        borderRadius: any;
        zIndex: any;
        orient: any;
        progressVisible: any;
        onchangeProgress: any;
        tabindex: any;

        constructor(id, options, guiMgr: UIMgr, callback, append) {
            super(guiMgr.canvas, guiMgr.canvasCss, options);
            if (append == null || append == undefined) { append = true; }

            var signe = "";
            if (this.pixel) { signe = "px"; }
            else { signe = "%"; }

            this.progress = null;
            this.id = id;
            this.html = document.body || document.getElementsByTagName('body')[0];
            this.progressPosition = { x: options.x, y: options.y };
            this.progressSize = { width: options.w, height: options.h };
            this.min = options.min || 0;
            this.max = options.max || 100;
            this.value = options.value || 0;
            this.border = options.border || 0;
            this.background = options.background || null;
            this.backgroundValue = options.backgroundValue || null;
            this.borderRadius = options.borderRadius || (options.h / 2) + signe;
            this.zIndex = options.zIndex || 1;
            this.orient = options.orient || "horizontal"; // or "vertical"
            this.progressVisible = true;
            this.onchangeProgress = callback || "";
            this.tabindex = options.tabindex || 0;

            if (append == true) {
                this.addElement(append, null);
            }
        }

        addElement(append, element) {
            var signe = "";
            if (this.pixel) { signe = "px"; }
            else { signe = "%"; }
            this.progress = document.createElement("progress");
            this.progress.min = this.min;
            this.progress.max = this.max;
            this.progress.value = this.value;
            this.progress.style.width = this.progressSize.width + "%";
            this.progress.style.height = this.progressSize.height + "%";
            if (this.convertPixelToPercent == true) {
                if (append == true) {
                    this.progress.style.top = this.convertPixelToPercentWidth(this.progressPosition.y + this.getCanvasOrigine().top) + "%";
                    this.progress.style.left = this.convertPixelToPercentHeight(this.progressPosition.x + this.getCanvasOrigine().left) + "%";
                } else {
                    this.progress.style.top = (this.progressPosition.y) + "px";
                    this.progress.style.left = (this.progressPosition.x) + "px";
                }
            } else {
                if (append == true) {
                    this.progress.style.top = (this.progressPosition.y + this.getCanvasOrigine().top) + signe;
                    this.progress.style.left = (this.progressPosition.x + this.getCanvasOrigine().left) + signe;
                } else {
                    this.progress.style.top = (this.progressPosition.y) + signe;
                    this.progress.style.left = (this.progressPosition.x) + signe;
                }
            }
            this.progress.style.position = "absolute";
            this.progress.id = this.id;
            this.progress.className = "GUIProgress";
            this.progress.tabindex = this.tabindex;
            this.progress.name = this.id;
            this.progress.style.zIndex = this.zIndex;
            if (this.orient == "vertical" || this.orient == "Vertical") {
                this.progress.style.writingMode = "bt-lr";
                this.progress.style.WebkitAppearance = "progress-vertical";
            }

            var cssProgress = "#" + this.id + " {" +
                "border:" + this.border + ";" +
                "border-radius:" + this.borderRadius + ";" +
                "background-color:" + this.background + ";" +
                "} #" + this.id + "::after {" +
                "border:" + this.border + ";" +
                "border-radius:" + this.borderRadius + ";" +
                "background-color:" + this.backgroundValue + ";" +
                "} #" + this.id + "::-webkit-progress-bar {" +
                "border:" + this.border + ";" +
                "border-radius:" + this.borderRadius + ";" +
                "background-color:" + this.background + ";" +
                "} #" + this.id + "::-webkit-progress-value {" +
                "border:" + this.border + ";" +
                "border-radius:" + this.borderRadius + ";" +
                "background-color:" + this.backgroundValue + ";" +
                "} #" + this.id + "::-moz-progress-bar {" +
                "border:" + this.border + ";" +
                "border-radius:" + this.borderRadius + ";" +
                "background-color:" + this.background + ";" +
                "}";
            this.addStyle(cssProgress);

            this.progress.onchange = this.onchangeProgress;

            if (append == true) {
                this.html.appendChild(this.progress);
            } else {
                element.appendChild(this.progress);
            }
            this.addGuiElements(this.progress);
        }

        addStyle(css) {
        }

        setValue(value) {
            this.progress.value = value;
        }

        getValue() {
            return this.progress.value;
        }

        dispose() {
            return this.html.removeChild(this.getElementById(this.id));
        }

        setVisible(bool, fade) {
            var display;
            if (fade == undefined) fade = true;
            var element = this.getElementById(this.id);
            if (bool == true) {
                display = "block";
                this.progressVisible = true;
                if (fade == true) { this.fadeIn(element); }
            } else {
                display = "none";
                this.progressVisible = false;
                if (fade == true) { this.fadeOut(element); }
            }
            if (fade == false) { element.style.display = display; }
        }

        isVisible(): boolean {
            return this.progressVisible;
        }

    }

    //
    export class UISelect extends UIMgr {
        selectPosition: any;
        selectSize: any;
        zIndex: any;
        selectVisible: any;
        onchangeSelectoptions: any;
        tabindex: any;
        optionsListe: any;
        append: any;

        constructor(id, options, guiMgr: UIMgr, callback, append) {
            super(guiMgr.canvas, guiMgr.canvasCss, options);
            if (append == null || append == undefined) { append = true; }

            this.id = id;
            this.html = document.body || document.getElementsByTagName('body')[0];
            this.selectPosition = { x: options.x, y: options.y };
            this.selectSize = { width: options.w, height: options.h };
            this.zIndex = options.zIndex || 1;
            this.selectVisible = true;
            this.onchangeSelectoptions = callback || false;
            this.tabindex = options.tabindex || 0;
            this.optionsListe = [];
            this.append = append;

            if (this.append == true) {
                this.addElement(this.append, null);
            }
        }

        addElement(append, element) {
            var signe = "";
            if (this.pixel) { signe = "px"; }
            else { signe = "%"; }
            var that = this;
            var select = document.createElement("select");
            select.style.width = this.selectSize.width + "px";
            select.style.height = this.selectSize.height + "px";
            if (this.convertPixelToPercent == true) {
                if (append == true) {
                    select.style.top = this.convertPixelToPercentHeight(this.selectPosition.y + this.getCanvasOrigine().top) + "%";
                    select.style.left = this.convertPixelToPercentWidth(this.selectPosition.x + this.getCanvasOrigine().left) + "%";
                } else {
                    select.style.top = (this.selectPosition.y) + "px";
                    select.style.left = (this.selectPosition.x) + "px";
                }
            } else {
                if (append == true) {
                    select.style.top = (this.selectPosition.y + this.getCanvasOrigine().top) + signe;
                    select.style.left = (this.selectPosition.x + this.getCanvasOrigine().left) + signe;
                } else {
                    select.style.top = this.selectPosition.y + signe;
                    select.style.left = this.selectPosition.x + signe;
                }
            }
            select.style.position = "absolute";
            select.id = this.id;
            select.name = this.id;
            select.className = "GUISelect";
            select.tabIndex = this.tabindex;
            select.style.zIndex = this.zIndex;
            select.onchange = this.onchangeSelectoptions;

            if (append == true) {
                this.html.appendChild(select);
            } else {
                element.appendChild(select);
                this.optionsListe.forEach(function (options) {
                    that.getElementById(that.id).appendChild(options);
                });
            }

            this.addGuiElements(select);
        }

        addOptions(value, text) {
            var options = document.createElement("option");
            options.value = value;
            options.innerHTML = text;
            if (this.append == false) {
                this.optionsListe.push(options);
            } else {
                this.getElementById(this.id).appendChild(options);
            }
        }

        findOptionSelected(withIndex) {
            if (withIndex == undefined) withIndex = false;
            var elSel: HTMLSelectElement = <HTMLSelectElement>(this.getElementById(this.id));
            var str = elSel.options[elSel.selectedIndex].textContent;
            if (withIndex == true) {
                return elSel.selectedIndex.toString();
            } else {
                return str;
            }
        }

        removeOption(value) {
            var elSel: HTMLSelectElement = <HTMLSelectElement>(this.getElementById(this.id));
            for (var i = 0; i < elSel.length; i++) {
                if (elSel.options[i].textContent == value) {
                    elSel.remove(i);
                    break;
                }
            }
            if (this.append == false) {
                for (var b in this.optionsListe) {
                    if (this.optionsListe[b] == value) {
                        this.optionsListe.splice(b, 1);
                        break;
                    }
                }
            }
            return;
        }

        changeItem(oldValue, newValue) {
            var elSel: HTMLSelectElement = <HTMLSelectElement>(this.getElementById(this.id));
            for (var i = 0; i < elSel.length; i++) {
                if (elSel.options[i].textContent == oldValue) {
                    elSel.options[i].textContent = newValue;
                    elSel.options[i].nodeValue = newValue;
                    break;
                }
            }
            return;
        }

        selectedItem(item) {
            var elSel: HTMLSelectElement = <HTMLSelectElement>(this.getElementById(this.id));
            for (var i = 0; i < elSel.length; i++) {
                if (elSel.options[i].textContent == item) {
                    elSel.options[i].setAttribute('selected', 'true');
                } else {
                    elSel.options[i].removeAttribute('selected');
                }
            }
            return;
        }

        dispose() {
            return this.html.removeChild(this.getElementById(this.id));
        }

        setVisible(bool, fade) {
            var display;
            if (fade == undefined) fade = true;
            var element = this.getElementById(this.id);
            if (bool == true) {
                display = "block";
                this.selectVisible = true;
                if (fade == true) { this.fadeIn(element); }
            } else {
                display = "none";
                this.selectVisible = false;
                if (fade == true) { this.fadeOut(element); }
            }
            if (fade == false) { element.style.display = display; }
        }

        isVisible(): boolean {
            return this.selectVisible;
        }

    }

    //
    export class UISlider extends UIMgr {
        sliderPosition: any;
        sliderSize: any;
        min: any;
        max: any;
        step: any;
        value: any;
        zIndex: any;
        orient: any;
        sliderVisible: any;
        onchangeSlider: any;
        tabindex: any;

        constructor(id, options, guiMgr: UIMgr, callback, append) {
            super(guiMgr.canvas, guiMgr.canvasCss, options);
            if (append == null || append == undefined) { append = true; }

            this.id = id;
            this.html = document.body || document.getElementsByTagName('body')[0];
            this.sliderPosition = { x: options.x, y: options.y };
            this.sliderSize = { width: options.w, height: options.h };
            this.min = options.min || 0;
            this.max = options.max || 100;
            this.step = options.step || 1;
            this.value = options.value || (this.max / 2);
            this.zIndex = options.zIndex || 1;
            this.orient = options.orient || "horizontal"; // or "vertical"
            this.sliderVisible = true;
            this.onchangeSlider = callback || false;
            this.tabindex = options.tabindex || 0;

            if (append == true) {
                this.addElement(append, null);
            }
        }

        addElement(append, element) {
            var signe = "";
            if (this.pixel) { signe = "px"; }
            else { signe = "%"; }
            var slider = document.createElement("input");
            slider.type = "range";
            slider.min = this.min;
            slider.max = this.max;
            slider.value = this.value;
            slider.step = this.step;
            slider.className = "GUISlider";
            slider.tabIndex = this.tabindex;
            slider.style.width = this.sliderSize.width + "px";
            slider.style.height = this.sliderSize.height + "px";
            if (this.convertPixelToPercent == true) {
                if (append == true) {
                    slider.style.top = this.convertPixelToPercentHeight(this.sliderPosition.y + this.getCanvasOrigine().top) + "%";
                    slider.style.left = this.convertPixelToPercentWidth(this.sliderPosition.x + this.getCanvasOrigine().left) + "%";
                } else {
                    slider.style.top = (this.sliderPosition.y) + "px";
                    slider.style.left = (this.sliderPosition.x) + "px";
                }
            } else {
                if (append == true) {
                    slider.style.top = (this.sliderPosition.y + this.getCanvasOrigine().top) + signe;
                    slider.style.left = (this.sliderPosition.x + this.getCanvasOrigine().left) + signe;
                } else {
                    slider.style.top = this.sliderPosition.y + signe;
                    slider.style.left = this.sliderPosition.x + signe;
                }
            }
            slider.style.position = "absolute";
            slider.id = this.id;
            slider.name = this.id;
            slider.style.zIndex = this.zIndex;
            if (this.orient == "vertical" || this.orient == "Vertical") {
                slider.style.writingMode = "bt-lr";
                slider.style.webkitAppearance = "slider-vertical";
            }
            slider.oninput = this.onchangeSlider;
            slider.onchange = this.onchangeSlider;

            if (append == true) {
                this.html.appendChild(slider);
            } else {
                element.appendChild(slider);
            }
            this.addGuiElements(slider);
        }

        getValue() {
            return this.getElementById(this.id).nodeValue;
        }

        dispose() {
            return this.html.removeChild(this.getElementById(this.id));
        }

        setVisible(bool, fade) {
            var display;
            if (fade == undefined) fade = true;
            var element = this.getElementById(this.id);
            if (bool == true) {
                display = "block";
                this.sliderVisible = true;
                if (fade == true) { this.fadeIn(element); }
            } else {
                display = "none";
                this.sliderVisible = false;
                if (fade == true) { this.fadeOut(element); }
            }
            if (fade == false) { element.style.display = display; }
        }

        isVisible(): boolean {
            return this.sliderVisible;
        }

    }

    //
    export class UISpinner extends UIMgr {
        numberPosition: any;
        numberSize: any;
        min: any;
        max: any;
        step: any;
        value: any;
        zIndex: any;
        orient: any;
        numberVisible: any;
        onchangeNumber: any;
        tabindex: any;

        constructor(id, options, guiMgr: UIMgr, callback, append) {
            super(guiMgr.canvas, guiMgr.canvasCss, options);
            if (append == null || append == undefined) { append = true; }

            this.id = id;
            this.html = document.body || document.getElementsByTagName('body')[0];
            this.numberPosition = { x: options.x, y: options.y };
            this.numberSize = { width: options.w, height: options.h };
            this.min = options.min || 0;
            this.max = options.max || 100;
            this.step = options.step || 1;
            this.value = options.value || (this.max / 2);
            this.zIndex = options.zIndex || 1;
            this.orient = options.orient || "horizontal"; // or "vertical"
            this.numberVisible = true;
            this.onchangeNumber = callback || false;
            this.tabindex = options.tabindex || 0;

            if (append == true) {
                this.addElement(append, null);
            }
        }

        addElement(append, element) {
            var signe = "";
            if (this.pixel) { signe = "px"; }
            else { signe = "%"; }
            var number = document.createElement("input");
            number.type = "number";
            number.min = this.min;
            number.max = this.max;
            number.value = this.value;
            number.step = this.step;
            number.style.width = this.numberSize.width + signe;
            number.style.height = this.numberSize.height + signe;
            if (this.convertPixelToPercent == true) {
                if (append == true) {
                    number.style.top = this.convertPixelToPercentHeight(this.numberPosition.y + this.getCanvasOrigine().top) + "%";
                    number.style.left = this.convertPixelToPercentWidth(this.numberPosition.x + this.getCanvasOrigine().left) + "%";
                } else {
                    number.style.top = (this.numberPosition.y) + "px";
                    number.style.left = (this.numberPosition.x) + "px";
                }
            } else {
                if (append == true) {
                    number.style.top = (this.numberPosition.y + this.getCanvasOrigine().top) + signe;
                    number.style.left = (this.numberPosition.x + this.getCanvasOrigine().left) + signe;
                } else {
                    number.style.top = this.numberPosition.y + signe;
                    number.style.left = this.numberPosition.x + signe;
                }
            }
            number.style.position = "absolute";
            number.id = this.id;
            number.name = this.id;
            number.className = "GUISpinner";
            number.tabIndex = this.tabindex;
            number.style.zIndex = this.zIndex;
            number.oninput = this.onchangeNumber;
            number.onchange = this.onchangeNumber;

            if (append == true) {
                this.html.appendChild(number);
            } else {
                element.appendChild(number);
            }
            this.addGuiElements(number);
        }

        getValue() {
            return this.getElementById(this.id).nodeValue;
        }

        dispose() {
            return this.html.removeChild(this.getElementById(this.id));
        }

        setVisible(bool, fade) {
            var display;
            if (fade == undefined) fade = true;
            var element = this.getElementById(this.id);
            if (bool == true) {
                display = "block";
                this.numberVisible = true;
                if (fade == true) { this.fadeIn(element); }
            } else {
                display = "none";
                this.numberVisible = false;
                if (fade == true) { this.fadeOut(element); }
            }
            if (fade == false) { element.style.display = display; }
        }

        isVisible() {
            return this.numberVisible;
        }

    }

    //
    export class UIFieldset extends UIMgr {
        fieldsetPosition: any;
        fieldsetSize: any;
        legend: any;
        zIndex: any;
        fieldsetVisible: any;

        constructor(id, options, guiMgr: UIMgr, append) {
            super(guiMgr.canvas, guiMgr.canvasCss, options);
            if (append == null || append == undefined) { append = true; }

            this.id = id;
            this.html = document.body || document.getElementsByTagName('body')[0];
            this.fieldsetPosition = { x: options.x, y: options.y };
            this.fieldsetSize = { width: options.w, height: options.h };
            this.legend = options.legend;
            this.zIndex = options.zIndex || 1;
            this.fieldsetVisible = true;

            if (append == true) {
                this.addElement(append, null);
            }
        }

        addElement(append, element) {
            var signe = "";
            if (this.pixel) { signe = "px"; }
            else { signe = "%"; }
            var fieldset = document.createElement("fieldset");
            fieldset.style.width = this.fieldsetSize.width + "px";
            fieldset.style.height = this.fieldsetSize.height + "px";
            if (this.convertPixelToPercent == true) {
                if (append == true) {
                    fieldset.style.top = this.convertPixelToPercentHeight(this.fieldsetPosition.y + this.getCanvasOrigine().top) + "%";
                    fieldset.style.left = this.convertPixelToPercentWidth(this.fieldsetPosition.x + this.getCanvasOrigine().left) + "%";
                } else {
                    fieldset.style.top = (this.fieldsetPosition.y) + "px";
                    fieldset.style.left = (this.fieldsetPosition.x) + "px";
                }
            } else {
                if (append == true) {
                    fieldset.style.top = (this.fieldsetPosition.y + this.getCanvasOrigine().top) + signe;
                    fieldset.style.left = (this.fieldsetPosition.x + this.getCanvasOrigine().left) + signe;
                } else {
                    fieldset.style.top = (this.fieldsetPosition.y) + signe;
                    fieldset.style.left = (this.fieldsetPosition.x) + signe;
                }
            }
            fieldset.style.position = "absolute";
            fieldset.id = this.id;
            //fieldset.tagName = this.id;
            fieldset.className = "GUIFieldset";
            fieldset.style.zIndex = this.zIndex;
            this.html.appendChild(fieldset);
            var legend = document.createElement("legend");
            legend.innerHTML = this.legend;

            if (append == true) {
                this.getElementById(this.id).appendChild(legend);
            } else {
                element.appendChild(legend);
            }
            this.addGuiElements(fieldset);
        }

        add(element) {
            var contentFieldSet = this.getElementById(this.id);
            element.addElement(false, contentFieldSet);
        }

        dispose() {
            return this.html.removeChild(this.getElementById(this.id));
        }

        setVisible(bool, fade) {
            var display;
            if (fade == undefined) fade = true;
            var element = this.getElementById(this.id);
            if (bool == true) {
                display = "block";
                this.fieldsetVisible = true;
                if (fade == true) { this.fadeIn(element); }
            } else {
                display = "none";
                this.fieldsetVisible = false;
                if (fade == true) { this.fadeOut(element); }
            }
            if (fade == false) { element.style.display = display; }
        }

        isVisible(): boolean {
            return this.fieldsetVisible;
        }

    }

    


}