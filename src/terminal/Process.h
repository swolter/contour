/**
 * This file is part of the "libterminal" project
 *   Copyright (c) 2019 Christian Parpart <christian@parpart.family>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <map>
#include <optional>
#include <string>
#include <variant>
#include <vector>

#if defined(_MSC_VER)
#include <Windows.h>
#else
#include <pty.h>
#endif

namespace terminal {

class PseudoTerminal;

/**
 * Spawns and manages a child process with a pseudo terminal attached to it.
 */
class [[nodiscard]] Process {
  public:
#if defined(__unix__)
	using NativeHandle = pid_t;
#else
	using NativeHandle = HANDLE;
#endif

    struct NormalExit {
        int exitCode;
    };

    struct SignalExit {
        int signum;
    };

    struct Suspend {
    };

    struct Resume {
    };

    using ExitStatus = std::variant<NormalExit, SignalExit, Suspend, Resume>;
	using Environment = std::map<std::string, std::string>;

    //! Returns login shell of current user.
    static std::string loginShell();

    Process(
		PseudoTerminal& pty,
		const std::string& path,
		std::vector<std::string> const& args,
		Environment const& env
	);

	~Process();

	NativeHandle nativeHandle() const noexcept { return pid_; }

    [[nodiscard]] std::optional<ExitStatus> checkStatus() const;
	[[nodiscard]] ExitStatus wait();

private:
	mutable NativeHandle pid_{};

#if defined(_MSC_VER)
	PROCESS_INFORMATION processInfo_{};
	STARTUPINFOEX startupInfo_{};
#endif

    mutable std::optional<Process::ExitStatus> exitStatus_{};
};

}  // namespace terminal
