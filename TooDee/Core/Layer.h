#pragma once

#include "TooDee/Core/Base.h"
#include "TooDee/Core/TimeStep.h"
#include "TooDee/Events/Event.h"

namespace TooDee {
    class Layer
    {
        public:
            Layer(const std::string& name = "Layer");
            virtual ~Layer() = default;

            virtual void OnAttach() {}
            virtual void OnDetach() {}
            virtual void OnUpdate(TimeStep ts) {}
            virtual void OnImGuiRender() {}
            virtual void OnEvent(Event& event) {}

            const std::string& GetName() const { return m_debugName; }
        protected:
            std::string m_debugName;
    };
}
