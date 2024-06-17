/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "Log.h"

void FailureWriter(const char *data, size_t size) {}

std::string LogPath()
{
    return "log";
}

void InitGoogleLog(const char *argv0)
{
    const std::chrono::minutes keep{7 * 24 * 60};

    google::SetLogFilenameExtension(".log");
    google::EnableLogCleaner(keep);
    google::InstallFailureSignalHandler();
    google::InstallFailureWriter(FailureWriter);

    fLB::FLAGS_logtostdout = false;
    fLB::FLAGS_logtostderr = false;
    fLS::FLAGS_log_dir = LogPath();
    fLI::FLAGS_logbufsecs = 0;
    fLU::FLAGS_max_log_size = 10;
    fLB::FLAGS_stop_logging_if_full_disk = true;
    fLB::FLAGS_colorlogtostderr = true;
#if 0
    fLB::FLAGS_alsologtostderr = true;
#endif
    google::InitGoogleLogging(argv0);
}
