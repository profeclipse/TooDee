#pragma once

#include "TooDee/Core/Layer.h"

#include "TooDee/Events/ApplicationEvent.h"
#include "TooDee/Events/KeyEvent.h"
#include "TooDee/Events/MouseEvent.h"

namespace TooDee {
    class ImGuiLayer : public Layer
    {
        public:
            ImGuiLayer();
            ~ImGuiLayer() = default;

            virtual void OnAttach() override;
            virtual void OnDetach() override;
            virtual void OnEvent(Event& e) override;

            void Begin();
            void End();

            void BlockEvents(bool block) { m_BlockEvents = block; }

            void SetDarkThemeColors();

            uint32_t GetActiveWidgetID() const;

        private:
            bool m_BlockEvents = true;
    };
}
