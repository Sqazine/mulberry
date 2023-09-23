#include "GLShader.h"
#include <GL/glcorearb.h>
#include "GLUniform.h"
#include "Graphics/RHI/Shader.h"
#include "Core/Logger.h"
namespace mulberry
{

	GLShaderModule::GLShaderModule(ShaderType type, std::string_view content)
		: mShaderID(-1), mType(type)
	{
		mShaderID = glCreateShader(ToGLShaderType(type));
		auto sourceCode =ToGLShaderSourceCode(content);
		auto cSourceCode=sourceCode.c_str();
		glShaderSource(mShaderID, 1,&cSourceCode, nullptr);
		glCompileShader(mShaderID);
		VerifyCompile();
	}
	GLShaderModule::~GLShaderModule()
	{
		glDeleteShader(mShaderID);
	}

	const ShaderType &GLShaderModule::Type() const
	{
		return mType;
	}

	void GLShaderModule::VerifyCompile()
	{
		int32_t status;
		glGetShaderiv(mShaderID, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE)
		{
			char buffer[512];
			memset(buffer, 0, 512);
			glGetShaderInfoLog(mShaderID, 511, nullptr, buffer);
			MULBERRY_CORE_ERROR("GLSL compile failed:{}\n", buffer);
		}
	}

	GLShaderProgram::GLShaderProgram()
		: mTextureBindingIdx(0)
	{
		mProgramID = glCreateProgram();
	}
	GLShaderProgram::~GLShaderProgram()
	{
		glDeleteProgram(mProgramID);
	}

	void GLShaderProgram::SetActive(bool isActive)
	{
		if (isActive)
			glUseProgram(mProgramID);
		else
			glUseProgram(0);
	}

	void GLShaderProgram::SetTexture(std::string_view name, const GLTexture *texture)
	{
		glUniform1i(GetUniform(name), mTextureBindingIdx);
		glActiveTexture(GL_TEXTURE0 + mTextureBindingIdx);
		mTextureBindingIdx++;
		glBindTexture(GL_TEXTURE_2D, texture->GetHandle());
	}

	void GLShaderProgram::SetVertexArray(const GLVertexArray *vertexArray)
	{
		glBindVertexArray(vertexArray->mVertexArrayID);
	}
	void GLShaderProgram::ResetVertexArray()
	{
		glBindVertexArray(0);
	}

	void GLShaderProgram::ResetVertexBuffer(std::string_view name)
	{
		glDisableVertexAttribArray(GetAttribute(name));
	}

	bool GLShaderProgram::AttachShader(const GLShaderModule &shader)
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

	uint32_t GLShaderProgram::GetAttribute(std::string_view name) const
	{
		auto iter = mActiveAttributes.find(name.data());
		if (iter == std::end(mActiveAttributes))
		{
			MULBERRY_CORE_ERROR("bad attrib index:{}", name.data());
			return -1;
		}
		return iter->second;
	}
	uint32_t GLShaderProgram::GetUniform(std::string_view name) const
	{
		auto iter = mActiveUniforms.find(name.data());
		if (iter == std::end(mActiveUniforms))
		{
			MULBERRY_CORE_ERROR("bad uniform index:{}", name.data());
			return -1;
		}
		return iter->second;
	}

	void GLShaderProgram::PopulateAttributes()
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

	void GLShaderProgram::PopulateUniforms()
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

	bool GLShaderProgram::IsValidProgram()
	{
		int32_t status = GL_TRUE;
		glGetProgramiv(mProgramID, GL_LINK_STATUS, &status);
		if (status != GL_TRUE)
		{
			char buffer[512];
			memset(buffer, 0, 512);
			glGetProgramInfoLog(mProgramID, 512, nullptr, buffer);
			MULBERRY_CORE_ERROR("GLSL link status:{}\n", buffer);
			return false;
		}
		return true;
	}

}