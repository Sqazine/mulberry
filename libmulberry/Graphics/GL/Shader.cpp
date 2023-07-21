#include "Shader.h"
#include <GL/glcorearb.h>
#include <SDL2/SDL.h>
#include "Uniform.h"
#include <spdlog/spdlog.h>
namespace mulberry::gl
{

	ShaderModule::ShaderModule(const ShaderModuleType &type, std::string_view content)
		: mShaderID(-1), mType(type)
	{
		mShaderID = glCreateShader(type);
		const char *vCode = content.data();
		glShaderSource(mShaderID, 1, &vCode, nullptr);
		glCompileShader(mShaderID);
		VerifyCompile();
	}
	ShaderModule::~ShaderModule()
	{
		glDeleteShader(mShaderID);
	}

	const ShaderModuleType &ShaderModule::Type() const
	{
		return mType;
	}

	void ShaderModule::VerifyCompile()
	{
		int32_t status;
		glGetShaderiv(mShaderID, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE)
		{
			char buffer[512];
			memset(buffer, 0, 512);
			glGetShaderInfoLog(mShaderID, 511, nullptr, buffer);
			spdlog::error("GLSL compile failed:{}\n", buffer);
		}
	}

	ShaderProgram::ShaderProgram()
	{
		mProgramID = glCreateProgram();
	}
	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(mProgramID);
	}

	void ShaderProgram::SetActive(bool isActive)
	{
		if (isActive)
			glUseProgram(mProgramID);
		else
			glUseProgram(0);
	}

	bool ShaderProgram::AttachShader(const ShaderModule &shader)
	{
		glAttachShader(mProgramID, shader.mShaderID);
		glLinkProgram(mProgramID);

		bool validFlag = IsValidProgram();

		if (validFlag)
		{
			PopulateAttributes();
			PopulateUniforms();
		}

		return validFlag;
	}

	uint32_t ShaderProgram::GetAttribute(std::string_view name) const
	{
		auto iter = mActiveAttributes.find(name.data());
		if (iter == std::end(mActiveAttributes))
		{
			spdlog::error("bad attrib index:{}", name.data());
			return 0;
		}
		return iter->second;
	}
	uint32_t ShaderProgram::GetUniform(std::string_view name) const
	{
		auto iter = mActiveUniforms.find(name.data());
		if (iter == std::end(mActiveUniforms))
		{
			spdlog::error("bad uniform index:{}", name.data());
			return 0;
		}
		return iter->second;
	}

	void ShaderProgram::PopulateAttributes()
	{
		mActiveAttributes.clear();

		int32_t count = -1;
		int32_t length;
		char attribName[128];
		int32_t size;
		uint32_t type;

		SetActive(true);

		glGetProgramiv(mProgramID, GL_ACTIVE_ATTRIBUTES, &count);

		for (size_t i = 0; i < count; ++i)
		{
			memset(attribName, 0, sizeof(char) * 128);
			glGetActiveAttrib(mProgramID, i, 128, &length, &size, &type, attribName);
			int32_t attribIndex = glGetAttribLocation(mProgramID, attribName);

			if (attribIndex >= 0)
				mActiveAttributes[attribName] = attribIndex;
		}

		SetActive(false);
	}

	void ShaderProgram::PopulateUniforms()
	{
		mActiveUniforms.clear();

		int32_t count = -1;
		int32_t length;
		char uniformName[128];
		int32_t size;
		uint32_t type;

		SetActive(true);

		glGetProgramiv(mProgramID, GL_ACTIVE_UNIFORMS, &count);

		for (size_t i = 0; i < count; ++i)
		{
			memset(uniformName, 0, sizeof(char) * 128);
			glGetActiveUniform(mProgramID, i, 128, &length, &size, &type, uniformName);
			int32_t uniformIndex = glGetUniformLocation(mProgramID, uniformName);
			if (uniformIndex >= 0)
			{
				std::string name = uniformName;
				std::size_t found = name.find('[');

				if (found != std::string::npos) //uniform 数组
				{
					name.erase(name.begin() + found, name.end());
					uint32_t index = 0;
					char subName[256];
					while (1)
					{
						memset(subName, 0, sizeof(char) * 256);
						sprintf_s(subName, "%s[%d]", name.c_str(), index++);
						int32_t location = glGetUniformLocation(mProgramID, subName);
						if (location < 0)
							break;
						mActiveUniforms[subName] = location;
					}
				}
				//单个uniform
				mActiveUniforms[name] = uniformIndex;
			}
		}

		SetActive(false);
	}

	bool ShaderProgram::IsValidProgram()
	{
		int32_t status=GL_TRUE;
		glGetProgramiv(mProgramID, GL_LINK_STATUS, &status);
		if (status != GL_TRUE)
		{
			char buffer[512];
			memset(buffer, 0, 512);
			glGetProgramInfoLog(mProgramID, 512, nullptr, buffer);
			spdlog::error("GLSL link status:{}\n", buffer);
			return false;
		}
		return true;
	}

}