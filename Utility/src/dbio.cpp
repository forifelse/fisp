/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#include "../include/dbio.h"

namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		class DBPath
		------------------------------------------------------------*/
		DBPath::DBPath()
		{
			mstrData	= "data\\";
			mstrFile	= "";
			mstrApp		= "";
			mstrSource	= "source\\";
			mstrConfig	= "config\\";
			mstrStore	= "store\\";
			mstrUsers	= "users\\";
			mstrShader	= "shader\\";
			mstrWeb		= "web\\";
			mstrExePath = "";
			mstrDataPath = "";
		}

		DBPath::DBPath(const DBPath& other)
		{
			mstrData = other.mstrData;
			mstrFile = other.mstrFile;
			mstrApp = other.mstrApp;
			mstrSource = other.mstrSource;
			mstrConfig = other.mstrConfig;
			mstrStore = other.mstrStore;
			mstrUsers = other.mstrUsers;
			mstrShader = other.mstrShader;
			mstrWeb = other.mstrWeb;
			mstrExePath = other.mstrExePath;
			mstrDataPath = other.mstrDataPath;
		}

		void DBPath::setFileAndData(const String& file, const String& data)
		{
			fileField(file);
			dataField(data);
		}

		void DBPath::getFileAndData(String& file, String& data) const
		{
			file = fileField();
			data = dataField();
		}

		// only change data name. Default data name is "data".
		void DBPath::dataName(const String& strDataName)
		{
			if (strDataName.isEmpty())
				return;
			mstrData = "..\\";
			mstrData += strDataName;
			mstrData += "\\";
		}

		void DBPath::dataField(const String& strData)
		{
			mstrData = strData;
		}

		const String& DBPath::dataField() const
		{
			return mstrData;
		}

		void DBPath::fileField(const String& file)
		{
			mstrFile = file;
		}

		const String& DBPath::fileField() const
		{
			return mstrFile;
		}

		void DBPath::appField(const String& strApp)
		{
			if (!strApp.isEmpty())
			{
				mstrApp = strApp + "\\";
			}
			else
			{
				mstrApp = "";
			}
		}

		const String& DBPath::appField() const
		{
			return mstrApp;
		}

		void DBPath::sourceField(const String& path)
		{
			mstrSource = path;
		}

		String DBPath::source(bool absolute /*= true*/) const
		{
			if (absolute)
			{
				return mstrDataPath + mstrSource;
			}
			return mstrSource;
		}

		void DBPath::configField(const String& path)
		{
			mstrConfig = path;
		}

		String DBPath::config(bool absolute /*= true*/) const
		{
			if (absolute)
			{
				return mstrDataPath + mstrConfig;
			}
			return mstrConfig;
		}

		void DBPath::storeField(const String& path)
		{
			mstrStore = path;
		}

		String DBPath::store(bool absolute /* = true */) const
		{
			if (absolute)
			{
				return mstrDataPath + mstrStore;
			}
			return mstrStore;
		}

		void DBPath::usersField(const String& path)
		{
			mstrUsers = path;
		}

		String DBPath::users(bool absolute /* = true */) const
		{
			if (absolute)
			{
				return mstrDataPath + mstrUsers;
			}
			return mstrUsers;
		}

		void DBPath::shaderField(const String& path)
		{
			mstrShader = path;
		}

		String DBPath::shader(bool absolute /*= true*/) const
		{
			if (absolute)
			{
				return mstrDataPath + mstrShader;
			}
			return mstrShader;
		}

		void DBPath::webField(const String& path)
		{
			mstrWeb = path;
		}

		String DBPath::web(bool absolute /* = true */) const
		{
			if (absolute)
			{
				return mstrDataPath + mstrWeb;
			}
			return mstrWeb;
		}

		const String& DBPath::exePath() const
		{
			return mstrExePath;
		}

		void DBPath::exePath(const String& path)
		{
			mstrExePath = path;
		}

		const String& DBPath::dataPath() const
		{
			return mstrDataPath;
		}

		void DBPath::dataPath(int uPreDirectory)
		{
			if (uPreDirectory < 0)
			{
				mstrDataPath = mstrData;
				return;
			}
			if (uPreDirectory == 0)
			{
				mstrDataPath = mstrExePath + mstrData;
				return;
			}
			//
			String str = mstrExePath;
			ulong uIdx = 0, uFrom = str.getSize() - 1;
			while (uPreDirectory >= 0 && str.find(String("\\"), uIdx, uFrom, true))
			{
				if (uIdx <= 0)
				{
					mstrDataPath = mstrData;
					return;
				}
				uFrom = uIdx - 1;
				uPreDirectory--;
			}
			uFrom++;
			str.remove(uFrom, str.getSize() - uFrom);
			mstrDataPath = str + "\\" + mstrData;
		}

		void DBPath::fromPath(const String& strPath, int uPreDirectory)
		{
			mstrExePath = extractPath(strPath, 0);
			mstrDataPath = extractPath(strPath, uPreDirectory) + mstrData;
		}

		String DBPath::extractPath(const String& strPath, int uPreDirectory)
		{
			String strFinalPath;
			if (uPreDirectory < 0)
			{
				uPreDirectory = 0;
			}
			//
			String str = strPath;
			ulong uIdx = 0, uFrom = str.getSize() - 1;
			while (uPreDirectory >= 0 && str.find(String("\\"), uIdx, uFrom, true))
			{
				if (uIdx <= 0)
				{
					strFinalPath = "";
					return strFinalPath;
				}
				uFrom = uIdx - 1;
				uPreDirectory--;
			}
			uFrom++;
			str.remove(uFrom, str.getSize() - uFrom);
			strFinalPath = str + "\\";
			//
			return strFinalPath;
		}



	}
}