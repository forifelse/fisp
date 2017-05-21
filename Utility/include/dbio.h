/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "base.h"

namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		class IDBPath
		------------------------------------------------------------*/
		class IDBPath : public IRoot
		{
		public:
			virtual void setFileAndData(const String& file, const String& data) = 0;
			virtual void getFileAndData(String& file, String& data) const = 0;
			// only change data name. Default data name is "data".
			virtual void dataName(const String& strDataName) = 0;
			virtual void dataField(const String& strData) = 0;
			virtual const String& dataField() const = 0;
			virtual void fileField(const String& file) = 0;
			virtual const String& fileField() const = 0;
			virtual void appField(const String& strApp) = 0;
			virtual const String& appField() const = 0;
			virtual void sourceField(const String& path) = 0;
			virtual String source(bool absolute = true) const = 0;
			virtual void configField(const String& path) = 0;
			virtual String config(bool absolute = true) const = 0;
			virtual void storeField(const String& path) = 0;
			virtual String store(bool absolute = true) const = 0;
			virtual void usersField(const String& path) = 0;
			virtual String users(bool absolute = true) const = 0;
			virtual void shaderField(const String& path) = 0;
			virtual String shader(bool absolute = true) const = 0;
			virtual void webField(const String& path) = 0;
			virtual String web(bool absolute = true) const = 0;
			virtual const String& exePath() const = 0;
			virtual void exePath(const String& path) = 0;
			virtual const String& dataPath() const = 0;
			virtual void dataPath(int uPreDirectory) = 0;

		};

		/*-----------------------------------------------------------
		class DBPath
		------------------------------------------------------------*/
		class DBPath : public IDBPath
		{
		public:
			void setFileAndData(const String& file, const String& data) override;
			void getFileAndData(String& file, String& data) const override;
			// only change path name. Default path name is "data".
			void dataName(const String& strDataName) override;
			void dataField(const String& strData) override;
			const String& dataField() const override;
			void fileField(const String& file) override;
			const String& fileField() const override;
			void appField(const String& strApp) override;
			const String& appField() const override;
			void sourceField(const String& path) override;
			String source(bool absolute = true) const override;
			void configField(const String& path) override;
			String config(bool absolute = true) const override;
			void storeField(const String& path) override;
			String store(bool absolute = true) const override;
			void usersField(const String& path) override;
			String users(bool absolute = true) const override;
			void shaderField(const String& path) override;
			String shader(bool absolute = true) const override;
			void webField(const String& path) override;
			String web(bool absolute = true) const override;
			const String& exePath() const override;
			void exePath(const String& path) override;
			virtual const String& dataPath() const override;
			virtual void dataPath(int uPreDirectory) override;

		public:
			DBPath();
			DBPath(const DBPath& other);
			void fromPath(const String& strPath, int uPreDirectory);

			static String extractPath(const String& strPath, int uPreDirectory);

		protected:
			String	mstrData;		// Only data path, not include file name.
			String	mstrFile;		// Only file name , not include path.
			String	mstrApp;		// app imp name used to specify sub path.
			String	mstrSource;		// relative path , not absolute path.
			String	mstrConfig;		// relative path , not absolute path.
			String	mstrStore;		// relative path , not absolute path.
			String	mstrUsers;		// relative path , not absolute path.
			String	mstrShader;		// relative path , not absolute path.
			String	mstrWeb;		// relative path , not absolute path.
			String	mstrExePath;	// absolute exe path.
			String	mstrDataPath;	// absolute data path.
		};


	}
}
