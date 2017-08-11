/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _DEBUGGERD_TOMBSTONE_H
#define _DEBUGGERD_TOMBSTONE_H

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

#include <map>
#include <string>

#include "open_files_list.h"

class BacktraceMap;

/* Create and open a tombstone file for writing.
 * Returns a writable file descriptor, or -1 with errno set appropriately.
 * If out_path is non-null, *out_path is set to the path of the tombstone file.
 */
int open_tombstone(std::string* path);

/* Creates a tombstone file and writes the crash dump to it. */
void engrave_tombstone(int tombstone_fd, BacktraceMap* map, BacktraceMap* map_new,
                       const OpenFilesList* open_files, pid_t pid, pid_t tid,
                       const std::string& process_name, const std::map<pid_t, std::string>& threads,
                       uintptr_t abort_msg_address, std::string* amfd_data);

void engrave_tombstone_ucontext(int tombstone_fd, uintptr_t abort_msg_address, siginfo_t* siginfo,
                                ucontext_t* ucontext);

// Compatibility shim.
__attribute__((__unused__))
static void engrave_tombstone_ucontext(int tombstone_fd, pid_t, pid_t, uintptr_t abort_msg_address,
                                       siginfo_t* siginfo, ucontext_t* ucontext) {
  engrave_tombstone_ucontext(tombstone_fd, abort_msg_address, siginfo, ucontext);
}

#endif // _DEBUGGERD_TOMBSTONE_H
