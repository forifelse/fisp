namespace Fisp {
    export class Matrix {
    }

    //
    export class Utility {

        static isZero(val) {
            var bZero = (val > -0.0000001 && val < 0.0000001);
            return bZero;
        }

        static strLength = function (str) {
            var cArr = str.match(/[^\x00-\xff]/ig);
            return str.length + (cArr == null ? 0 : cArr.length);
        }

        static colorFromHexString = function (hex) {
            if (hex.substring(0, 1) !== "#" || hex.length != 7) {
                //Fisp.Msgbox.showMsg("Color3.FromHexString must be called with a string like #FFFFFF");
                return [0, 0, 0];
            }
            var r = parseInt(hex.substring(1, 3), 16) / 255.0;
            var g = parseInt(hex.substring(3, 5), 16) / 255.0;
            var b = parseInt(hex.substring(5, 7), 16) / 255.0;
            return [r, g, b];
        }

        static downloadFile = function (url) {
            if (url)
                window.location.href = url;
        }

        static runExe = function (strPath) {
            try {
                var objShell = new ActiveXObject("wscript.shell");
                objShell.Run(strPath);
                objShell = null;
            } catch (e) {
                alert('找不到文件"' + strPath + '"(或它的组件之一)。请确定路径和文件名是否正确.');
                alert(e.message);
                alert(e.description);
                alert(e.number);
                alert(e.name);
            }
            //window.open("index.html");
        }

        static removeEle<T>(list: Array<T>): Array<T> {
            var newList: Array<T> = [];
            return newList;
        }

    }

    //
    export class NetData {

        constructor() {
        }

        static getData(url, procData: Function) {
            var xhr = new XMLHttpRequest();
            var id = null;
            var pw = null;
            xhr.open('GET', url, true, id, pw);
            xhr.send();
            xhr.onreadystatechange = function () {
                if (this.readyState == this.DONE) {
                    if (this.status == 200) {// ok!
                        procData(xhr.responseText);
                        return;
                    }
                    else {// error
                        //procData(null);
                        alert('parse ' + url + ' error!');
                    }
                }
            }
            //xhr.onload = function (evt){
            //};
        }

        static putData(url, msg) {
            var xhr = new XMLHttpRequest();
            //var url = "img/test.json";
            var id = null;
            var pw = null;
            xhr.open('POST', url, true, id, pw);
            xhr.setRequestHeader("Content-Type", "text/plain;charset=UTF-8");
            xhr.send(msg);
            xhr.onreadystatechange = function () {
                if (this.readyState == this.DONE) {
                    alert('status: ' + this.status);
                    if (this.status == 200) {
                        // ok!
                        var val = xhr.responseText;
                        //procData();
                        //document.write(val);
                        alert('ok: ' + val);
                        return;
                    }
                    else {
                        // error
                        //procData(null);
                    }
                }
            }
            xhr.onload = function (evt) {
                alert('onload');
            };
        }

        fetchStatus(address) {
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function () {
                //
                if (this.readyState == this.DONE) {
                }
            }
            xhr.open("HEAD", address);
            xhr.send();
        }


    }

    //
    export class NetDatabase {
        database: any;

        constructor(useSessionStorage) {
            if (useSessionStorage == undefined || useSessionStorage == false) {
                this.database = window.localStorage;
            } else {
                this.database = window.sessionStorage;
            }
        }

        deleteDataBase() {
            this.database.clear();
        }

        deleteTable(table) {
            this.database.removeItem(table);
        }

        deleteField(table, field) {
            var champ = table[field];
            this.database.removeItem(champ);
        }

        deleteItemFromField(table, field, item) {
            var valeur = table[field][item];
            this.database.removeItem(item);
        }

        addTable(table) {
            var empty = JSON.stringify({});
            this.database.setItem(table, empty);
        }

        createField(table, field, value) {
            var data = JSON.stringify(value);
            var json = eval("({" + field + " : " + data + "})");
            this.database.setItem(table, JSON.stringify(json));
        }

        insertItemFromField(table, field, item, value) {
            var data = JSON.stringify(value);
            this.database.setItem(table[field][item], data);
        }

        selectItem(table, field, item) {
            var theTable = JSON.parse(this.database[table]);
            return theTable[field][item];

        }

        selectAllItems(table, field) {
            var theTable = JSON.parse(this.database[table][field]);
            return theTable;
        }

        selectAllTable(table) {
            var theTable = JSON.parse(this.database[table]);
            return theTable;
        }

        selectAllDataBase() {
            return JSON.parse(this.database);
        }

        updateItem(table, field, item, value) {
            this.database[table][field][item] = value;
        }

        getLimit() {
            return this.database.length - 1;
        }

        isSupported() {
            return (typeof localStorage != 'undefined') ? true : false;
        }

    }



}