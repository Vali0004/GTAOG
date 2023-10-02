#include "sprx_loader.h"
#define MOUNT_POINT SYS_DEV_HDD0"/tmp"

namespace sprxLoader {
	void directoryData::create() {
		u64 cursor{};
		m_dirPath = MOUNT_POINT"/GTAOG";
		s64 err{ cellFsOpendir(m_dirPath, &m_dirHandle) };
		if (err >= 0) {
			while (err = cellFsReaddir(m_dirHandle, &m_dirEntry, &cursor) >= 0) {
				if (!m_dirEntry.d_namlen) {
					break;
				}
				if (!(sstrstr(".", m_dirEntry.d_name) || sstrstr("..", m_dirEntry.d_name))) {
					m_files.push_back({ m_dirPath, m_dirEntry.d_name });
				}
				cursor++;
			}
			cellFsClosedir(m_dirHandle);
		}
	}
	void directoryData::destroy() {
		m_files.clear();
	}

	directoryData g_directoryData{ MOUNT_POINT"/GTAOG" };
	void create() {
		g_directoryData.create();
	}
	void loadAll() {
		for (fileData file : g_directoryData.files()) {
			if (file.m_fileType == eFileType::SPRX) {
				file.m_id = sys_prx_load_module(file.m_path, 0, NULL);
				s32 modres{ -1 };
				if (file.m_id <= 0) {
					g_logger.send("Info", "'%s' failed to load", file.m_name);
				}
				else {
					if (sys_prx_start_module(file.m_id, 0, NULL, &modres, 0, NULL) < 0) {
						g_logger.send("Info", "'%s' failed to start", file.m_name);
						sys_prx_unload_module(file.m_id, 0, NULL);
					}
				}
			}
		}
	}
	void unloadAll() {
		for (fileData file : g_directoryData.files()) {
			if (file.m_fileType == eFileType::SPRX) {
				s32 modres{ -1 };
				if (file.m_id <= 0) {
					g_logger.send("Info", "'%s' wasn't loaded", file.m_name);
				}
				else {
					if (sys_prx_stop_module(file.m_id, 0, NULL, &modres, 0, NULL) < 0) {
						g_logger.send("Info", "'%s' failed to stop", file.m_name);
					}
					sys_prx_unload_module(file.m_id, 0, NULL);
				}
			}
		}
	}
	void destroy() {
		g_directoryData.destroy();
	}
}