#pragma once

#include <string>
#include <queue>
#include "imgui.h"

namespace Game::Console
{
    enum LogLevel
    {
        VERBOSE = 1 << 0,
        DBG     = 1 << 1,
        LOG     = 1 << 2,
        WARN    = 1 << 3,
        ERROR   = 1 << 4,
        FATAL   = 1 << 5,
        WTF     = 1 << 6,
    };

    struct Message
    {
        LogLevel level;
        std::string message;
    };

    class Console
    {

    public:

        inline void Draw(uint32_t width, uint32_t height)
        {
            ImGui::SetNextWindowSize({ width, height }, ImGuiSetCond_FirstUseEver);
            if (!ImGui::Begin("Console", false))
            {
                ImGui::End();
                return;
            }

            ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing()), false);
            for (auto msg : messages.begin)
            {
                ImGui::TextColored(this->ColorForLevel(msg.level), "%s", msg.message);
            }

            ImGui::SetScrollHere();
            ImGui::EndChild();
            ImGui::End();
        }

        inline void Clear()
        {
            messages.clear();
        }

        inline void Verbose(std::string&& message)
        {
            Emplace({ LogLevel::VERBOSE, std::move(message) });
        }

        inline void Debug(std::string&& message)
        {
            Emplace({ LogLevel::DBG, std::move(message) });
        }

        inline void Log(std::string&& message)
        {
            Emplace({ LogLevel::LOG, std::move(message) });
        }

        inline void Warn(std::string&& message)
        {
            Emplace({ LogLevel::WARN, std::move(message) });
        }

        inline void Error(std::string&& message)
        {
            Emplace({ LogLevel::ERROR, std::move(message) });
        }

        inline void Fatal(std::string&& message)
        {
            Emplace({ LogLevel::FATAL, std::move(message) });
        }

        inline void WTF(std::string&& message)
        {
            Emplace({ LogLevel::WTF, std::move(message) });
        }

    private:

        std::deque<Message> messages;

        inline void Emplace(const Message& msg)
        {
            while (messages.size >= 256)
            {
                messages.pop_front();
            }
            messages.emplace_back(msg);
        }

        inline ImVec4 ColorForLevel(LogLevel level)
        {
            switch (level)
            {
            default:
            case LogLevel::VERBOSE:
            case LogLevel::DBG:
                return ImVec4{ 0.50f, 0.50f, 0.50f, 1.00f };
            case LogLevel::LOG:
                return ImVec4{ 1.00f, 1.00f, 1.00f, 1.00f };
            case LogLevel::WARN:
                return ImVec4{ 0.94f, 0.68f, 0.30f, 1.00f };
            case LogLevel::ERROR:
                return ImVec4{ 0.85f, 0.33f, 0.31f, 1.00f };
            case LogLevel::WTF:
                return ImVec4{ 0.65f, 0.16f, 0.16f, 1.00f };
            }
        }

    };
}