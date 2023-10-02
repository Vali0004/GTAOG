#pragma once
#include "include.h"
#include "logger/logger.h"

global bool mountDir(cc* path) {
	int err{};
	CellFsStat status{};
	for (int i{}; i != 15; ++i) {
		err = cellFsStat(path, &status);
		if (err == CELL_FS_SUCCEEDED) {
			return true;
		}
		SLEEP(1);
	}

	return false;
}
namespace sprxLoader {
	enum class eFileType : u8 {
		None,
		SPRX,
		PRX,
		SELF,
		ELF,
		Text,
		Unknown
	};
	class fileData {
	public:
		fileData(ccp path, ccp name) : m_name(name), m_path(string_combine(string_combine(path, "/"), name)) {
			if (!sstrstr(name, ".")) {
				m_fileType = eFileType::None;
			}
			else if (sstrstr(name, ".sprx")) {
				m_fileType = eFileType::SPRX;
			}
			else if (sstrstr(name, ".prx")) {
				m_fileType = eFileType::PRX;
			}
			else if (sstrstr(name, ".self")) {
				m_fileType = eFileType::SELF;
			}
			else if (sstrstr(name, ".elf")) {
				m_fileType = eFileType::ELF;
			}
			else if (sstrstr(name, ".txt")) {
				m_fileType = eFileType::Text;
			}
			else {
				m_fileType = eFileType::Unknown;
			}
		}
		eFileType m_fileType{};
		ccp m_path{};
		ccp m_name{};
		sys_prx_id_t m_id{};
	};
	class directoryData {
	public:
		directoryData(ccp path) : m_dirPath(path) {}
		~directoryData() {
			destroy();
		}
		void create();
		void destroy();
		vectorr<fileData> files() {
			return m_files;
		}
		ccp m_dirPath{};
	private:
		int m_dirHandle{};
		CellFsDirent m_dirEntry{};
		vectorr<fileData> m_files{};
	};
	extern directoryData g_directoryData;
	extern void create();
	extern void loadAll();
	extern void unloadAll();
	extern void destroy();
}