#include "GLShader.h"
#include "GLUniform.h"
#include "Graphics/RHI/Shader.h"
#include "Core/Logger.h"
namespace mulberry
{

	GLShader::GLShader(ShaderStage type, std::string_view content)
		: mShaderID(-1), mType(type)
	{
		mShaderID = glCreateShader(ToGLShaderStage(type));
		auto sourceCode =ToGLShaderSourceCode(content);
		auto cSourceCode=sourceCode.c_str();
		glShaderSource(mShaderID, 1,&cSourceCode, nullptr);
		glCompileShader(mShaderID);
		VerifyCompile();
	}
	GLShader::~GLShader()
	{
		glDeleteShader(mShaderID);
	}

	const ShaderStage &GLShader::Type() const
	{
		return mType;
	}

	void GLShader::VerifyCompile()
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

	GLShaderGroup::GLShaderGroup()
		: mTextureBindingIdx(0)
	{
		mProgramID = glCreateProgram();
	}
	GLShaderGroup::~GLShaderGroup()
	{
		glDeleteProgram(mProgramID);
	}

	void GLShaderGroup::SetActive(bool isActive)
	{
		if (isActive)
			glUseProgram(mProgramID);
		else
			glUseProgram(0);
	}

	void GLShaderGroup::SetTexture(std::string_view name, const GLTexture *texture)
	{
		auto iter=mActiveTextureSlot.find(name);
		if(iter==mActiveTextureSlot.end())
		{
			mActiveTextureSlot[name]=mTextureBindingIdx++;
			iter=mActiveTextureSlot.find(name);
		}

		glUniform1i(GetUniform(name), iter->second);
		glActiveTexture(GL_TEXTURE0 + iter->second);
		glBindTexture(GL_TEXTURE_2D, texture->GetHandle());
	}

	void GLShaderGroup::SetVertexArray(const GLVertexArray *vertexArray)
	{
		glBindVertexArray(vertexArray->mVertexArrayID);
	}
	void GLShaderGroup::ResetVertexArray()
	{
		glBindVertexArray(0);
	}

	void GLShaderGroup::ResetVertexBuffer(std::string_view name)
	{
		glDisableVertexAttribArray(GetAttribute(name));
	}

	bool GLShaderGroup::AttachShader(const GLShader &shader)
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

	uint32_t GLShaderGroup::GetAttribute(std::string_view name) const
	{
		auto iter = mActiveAttributes.find(name.data());
		if (iter == std::end(mActiveAttributes))
		{
			MULBERRY_CORE_ERROR("bad attrib index:{}", name.data());
			return -1;
		}
		return iter->second;
	}
	uint32_t GLShaderGroup::GetUniform(std::string_view name) const
	{
		auto iter = mActiveUniforms.find(name.data());
		if (iter == std::end(mActiveUniforms))
		{
			MULBERRY_CORE_ERROR("bad uniform index:{}", name.data());
			return -1;
		}
		return iter->second;
	}

	void GLShaderGroup::PopulateAttributes()
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

	void GLShaderGroup::PopulateUniforms()
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

	bool GLShaderGroup::IsValidProgram()
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