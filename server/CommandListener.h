/*
 * Copyright (C) 2008 The Android Open Source Project
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

#ifndef _COMMANDLISTENER_H__
#define _COMMANDLISTENER_H__

#include <mutex>

#include <android/net/INetd.h>
#include <sysutils/FrameworkListener.h>
#include "binder/IServiceManager.h"

#include "BandwidthController.h"
#include "ClatdController.h"
#include "FirewallController.h"
#include "IdletimerController.h"
#include "InterfaceController.h"
#include "NetdCommand.h"
#include "NetdConstants.h"

namespace android {
namespace net {

class CommandListener : public FrameworkListener {
  public:
    CommandListener();
    virtual ~CommandListener() {}

    static constexpr const char* SOCKET_NAME = "netd";
    static sp<INetd> mNetd;

  private:
    class InterfaceCmd : public NetdCommand {
    public:
        InterfaceCmd();
        virtual ~InterfaceCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    };

    class IpFwdCmd : public NetdCommand {
    public:
        IpFwdCmd();
        virtual ~IpFwdCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    };

    class TetherCmd : public NetdCommand {
    public:
        TetherCmd();
        virtual ~TetherCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    };

    class NatCmd : public NetdCommand {
    public:
        NatCmd();
        virtual ~NatCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    };

    class BandwidthControlCmd : public NetdCommand {
    public:
        BandwidthControlCmd();
        virtual ~BandwidthControlCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    protected:
        void sendGenericOkFail(SocketClient *cli, int cond);
        void sendGenericOpFailed(SocketClient *cli, const char *errMsg);
        void sendGenericSyntaxError(SocketClient *cli, const char *usageMsg);
    };

    class IdletimerControlCmd : public NetdCommand {
    public:
        IdletimerControlCmd();
        virtual ~IdletimerControlCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    };

    class FirewallCmd: public NetdCommand {
    public:
        FirewallCmd();
        virtual ~FirewallCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    protected:
        int sendGenericOkFail(SocketClient *cli, int cond);
        static int parseRule(const char* arg);
        static int parseFirewallType(const char* arg);
        static int parseChildChain(const char* arg);
    };

    class ClatdCmd : public NetdCommand {
    public:
        ClatdCmd();
        virtual ~ClatdCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    };

    class StrictCmd : public NetdCommand {
    public:
        StrictCmd();
        virtual ~StrictCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    protected:
        int sendGenericOkFail(SocketClient *cli, int cond);
        static int parsePenalty(const char* arg);
    };

    class NetworkCommand : public NetdCommand {
    public:
        NetworkCommand();
        virtual ~NetworkCommand() {}
        int runCommand(SocketClient* client, int argc, char** argv);
    private:
        int syntaxError(SocketClient* cli, const char* message);
        int operationError(SocketClient* cli, const char* message, int ret);
        int success(SocketClient* cli);
    };
};

}  // namespace net
}  // namespace android

#endif
