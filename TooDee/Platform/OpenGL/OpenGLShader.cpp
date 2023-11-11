#include "TooDee/Core/Base.h"
#include "TooDee/Platform/OpenGL/OpenGLShader.h"

#include <glad/glad.h>

namespace TooDee {
    namespace Utils {
        static uint32_t ShaderTypeFromString(const std::string& type)
        {
            if (type == "vertex")
                return GL_VERTEX_SHADER;
            if (type == "fragment" || type == "pixel")
                return GL_FRAGMENT_SHADER;

            TD_CORE_ASSERT(false,"Unknown shader type!");
            return 0;
        }

        static std::string StringFromShaderType(uint32_t type)
        {
            if (type == GL_VERTEX_SHADER)
                return "vertex";
            if (type == GL_FRAGMENT_SHADER)
                return "fragment";

            TD_CORE_ASSERT(false,"Unknown shader type!");
            return "";
        }
    }

    OpenGLShader::OpenGLShader(const std::string& filepath)
        : m_filePath(filepath)
    {
        std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);

        auto [vertexShader,fragmentShader] = CompileShaderBinaries(shaderSources);

        CreateProgram(vertexShader,fragmentShader);
    }

    OpenGLShader::OpenGLShader(const std::string& name,
            const std::string& vertexSrc,const std::string& fragmentSrc)
        : m_name(name)
    {
        std::unordered_map<uint32_t,std::string> shaderSources;
        shaderSources[GL_VERTEX_SHADER] = vertexSrc;
        shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;

        auto [vertexShader,fragmentShader] = CompileShaderBinaries(shaderSources);

        CreateProgram(vertexShader,fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_rendererID);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_rendererID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::SetInt(const std::string& name,int value)
    {
        UploadUniformInt(name,value);
    }

    void OpenGLShader::SetIntArray(const std::string& name,int* values,uint32_t count)
    {
        UploadUniformIntArray(name,values,count);
    }

    void OpenGLShader::SetFloat(const std::string& name,float value)
    {
        UploadUniformFloat(name,value);
    }

    void OpenGLShader::SetFloat2(const std::string& name,const glm::vec2& value)
    {
        UploadUniformFloat2(name,value);
    }

    void OpenGLShader::SetFloat3(const std::string& name,const glm::vec3& value)
    {
        UploadUniformFloat3(name,value);
    }

    void OpenGLShader::SetFloat4(const std::string& name,const glm::vec4& value)
    {
        UploadUniformFloat4(name,value);
    }

    void OpenGLShader::SetMat4(const std::string& name,const glm::mat4& value)
    {
        UploadUniformMat4(name,value);
    }

    void OpenGLShader::UploadUniformInt(const std::string& name,int value)
    {
        GLint location = glGetUniformLocation(m_rendererID,name.c_str());
        if (location < 0)
        {
            TD_CORE_ERROR("Unknown uniform variable '{0}'",name);
            TD_CORE_ASSERT(false,"Faled to set shader value"); 
        }
        glUniform1i(location,value);
    }

    void OpenGLShader::UploadUniformIntArray(const std::string& name,
            int* values,uint32_t count)
    {
        GLint location = glGetUniformLocation(m_rendererID,name.c_str());
        if (location < 0)
        {
            TD_CORE_ERROR("Unknown uniform variable '{0}'",name);
            TD_CORE_ASSERT(false,"Faled to set shader value"); 
        }
        glUniform1iv(location,count,values);
    }

    void OpenGLShader::UploadUniformFloat(const std::string& name,float value)
    {
        GLint location = glGetUniformLocation(m_rendererID,name.c_str());
        if (location < 0)
        {
            TD_CORE_ERROR("Unknown uniform variable '{0}'",name);
            TD_CORE_ASSERT(false,"Faled to set shader value"); 
        }
        glUniform1f(location,value);
    }

    void OpenGLShader::UploadUniformFloat2(const std::string& name,const glm::vec2& value)
    {
        GLint location = glGetUniformLocation(m_rendererID,name.c_str());
        if (location < 0)
        {
            TD_CORE_ERROR("Unknown uniform variable '{0}'",name);
            TD_CORE_ASSERT(false,"Faled to set shader value"); 
        }
        glUniform2f(location,value.x,value.y);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string& name,const glm::vec3& value)
    {
        GLint location = glGetUniformLocation(m_rendererID,name.c_str());
        if (location < 0)
        {
            TD_CORE_ERROR("Unknown uniform variable '{0}'",name);
            TD_CORE_ASSERT(false,"Faled to set shader value"); 
        }
        glUniform3f(location,value.x,value.y,value.z);
    }

    void OpenGLShader::UploadUniformFloat4(const std::string& name,const glm::vec4& value)
    {
        GLint location = glGetUniformLocation(m_rendererID,name.c_str());
        if (location < 0)
        {
            TD_CORE_ERROR("Unknown uniform variable '{0}'",name);
            TD_CORE_ASSERT(false,"Faled to set shader value"); 
        }
        glUniform4f(location,value.x,value.y,value.z,value.w);
    }

    void OpenGLShader::UploadUniformMat3(const std::string& name,const glm::mat3& matrix)
    {
        GLint location = glGetUniformLocation(m_rendererID,name.c_str());
        if (location < 0)
        {
            TD_CORE_ERROR("Unknown uniform variable '{0}'",name);
            TD_CORE_ASSERT(false,"Faled to set shader value"); 
        }
        glUniformMatrix3fv(location,1,GL_FALSE,glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name,const glm::mat4& matrix)
    {
        GLint location = glGetUniformLocation(m_rendererID,name.c_str());
        if (location < 0)
        {
            TD_CORE_ERROR("Unknown uniform variable '{0}'",name);
            TD_CORE_ASSERT(false,"Faled to set shader value"); 
        }
        glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(matrix));
    }

    std::string OpenGLShader::ReadFile(const std::string& filepath)
    {
        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary);

        if (in)
        {
            in.seekg(0,std::ios::end);
            size_t size = in.tellg();
            if (size != -1)
            {
                result.resize(size);
                in.seekg(0,std::ios::beg);
                in.read(&result[0],size);
            }
            else
            {
                TD_CORE_ERROR("Could not read from file '{0}'",filepath);
            }
        }
        else
        {
            TD_CORE_ERROR("Could not open file '{0}'",filepath);
        }

        return result;
    }

    std::unordered_map<uint32_t,std::string>
        OpenGLShader::PreProcess(const std::string& source)
    {
        std::unordered_map<uint32_t,std::string> shaderSources;

        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);

        size_t pos = source.find(typeToken, 0);
        while (pos != std::string::npos)
        {
            size_t eol = source.find_first_of("\r\n",pos);
            TD_CORE_ASSERT(eol != std::string::npos,"Syntax error");

            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin,eol-begin);
            TD_CORE_ASSERT(Utils::ShaderTypeFromString(type),
                    "Invalid shader type specified");

            size_t nextLinePos = source.find_first_not_of("\r\n",eol);
            TD_CORE_ASSERT(nextLinePos != std::string::npos,"Syntax error");

            pos = source.find(typeToken, nextLinePos);

            shaderSources[Utils::ShaderTypeFromString(type)] =
                (pos == std::string::npos) ?
                source.substr(nextLinePos) : source.substr(nextLinePos,pos-nextLinePos);
        }

        return shaderSources;
    }

    std::tuple<uint32_t,uint32_t> OpenGLShader::CompileShaderBinaries(
        const std::unordered_map<uint32_t,std::string>& shaderSources)
    {
        uint32_t vertexShader=0;
        uint32_t fragmentShader=0;
        uint32_t shader;

        for (auto [stage,source] : shaderSources)
        {
            switch (stage)
            {
                case GL_VERTEX_SHADER:
                    vertexShader = glCreateShader(GL_VERTEX_SHADER);
                    shader = vertexShader;
                    break;
                case GL_FRAGMENT_SHADER:
                    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                    shader = fragmentShader;
                    break;
            }

            const GLchar* data = source.c_str();
            glShaderSource(shader,1,&data,0);
            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader,GL_COMPILE_STATUS,&isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader,maxLength,&maxLength,&infoLog[0]);

                if (vertexShader != 0)
                    glDeleteShader(vertexShader);
                if (fragmentShader != 0)
                    glDeleteShader(fragmentShader);

                TD_CORE_ERROR("{0}",infoLog.data());
                if (stage == GL_VERTEX_SHADER)
                    TD_CORE_ASSERT(false,"Failed to compile vertex shader!");
                else
                    TD_CORE_ASSERT(false,"Failed to compile fragment shader!");

                return { 0,0 };
            }
        }

        return { vertexShader,fragmentShader };
    }

    void OpenGLShader::CreateProgram(uint32_t vertexShader,uint32_t fragmentShader)
    {
        m_rendererID = glCreateProgram();

        glAttachShader(m_rendererID,vertexShader);
        glAttachShader(m_rendererID,fragmentShader);

        glLinkProgram(m_rendererID);

        GLint isLinked = 0;
        glGetProgramiv(m_rendererID,GL_LINK_STATUS,(int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_rendererID,GL_INFO_LOG_LENGTH,&maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_rendererID,maxLength,&maxLength,&infoLog[0]);

            glDeleteProgram(m_rendererID);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            TD_CORE_ERROR("{0}",infoLog.data());
            TD_CORE_ASSERT(false,"Shader link failure!");
            return;
        }

        glDetachShader(m_rendererID,vertexShader);
        glDetachShader(m_rendererID,fragmentShader);
    }
}
