#include <FRONTIER/Graphics/Shader.hpp>
#include <FRONTIER/Graphics/GLCheck.hpp>
#include <FRONTIER/Graphics/FgLog.hpp>
#include <FRONTIER/OpenGL.hpp>
//#include "glExtensionWrap.hpp"
#include <fstream>

namespace fg
{
	/// compile shader objects /////////////////////////////////////////////////////////
    unsigned int Shader::compileSubShader(const std::string &text,unsigned int type)
    {
        unsigned int s = glCreateShader(type);
		if (!s)
			fg_log<<"Couldn't create shader type "<<type<<std::endl;
		const char *c_text = text.c_str();
		const int length = text.length();
		glCheck(glShaderSource(s,1,&c_text,&length));
		glCheck(glCompileShader(s));
		int success;
		glCheck(glGetShaderiv(s, GL_COMPILE_STATUS, &success));
		if (success == 0)
		{
			int log_size;
			glCheck(glGetShaderiv(s, GL_INFO_LOG_LENGTH, &log_size));
			char *Log;
			Log = new char[log_size];
			glCheck(glGetShaderInfoLog(s, log_size, NULL, &Log[0]));
			fg_log<<"Error compiling shader type "<<type<<" : "<<Log<<std::endl;
			delete[] Log;
			return 0;
		}
		return s;
    }


	////////////////////////////////////////////////////////////
    unsigned int Shader::compileSubShaderFromFile(const std::string &file,unsigned int type)
    {
        std::ifstream in(file.c_str(), std::ios::in | std::ios::binary);
		if (in)
		{
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			return compileSubShader(contents,type);
		}
		fg_log<<"file "<<file<<" couldn't be read"<<std::endl;
		return 0;
    }
    
    ////////////////////////////////////////////////////////////
	void Shader::init()
	{
		if (!getGlId())
		{
			getGlId() = glCreateProgram();
			if (!getGlId())
				fg_log<<"couldn't create shader program"<<std::endl;			
		}
	}
    
    ////////////////////////////////////////////////////////////
	bool Shader::link()
	{
		init();
		if (!getGlId())
			return false;
		m_texCount = 0;
		m_textures.clear();
	    m_attribs.clear();
		m_uniforms.clear();
		C(m_subShaders.size())
			glCheck(glAttachShader(getGlId(),m_subShaders[i]));

		int success;
		glCheck(glLinkProgram(getGlId()));
		glCheck(glGetProgramiv(getGlId(), GL_LINK_STATUS, &success));
		if (!success)
		{
			int log_size;
			glCheck(glGetProgramiv(getGlId(), GL_INFO_LOG_LENGTH, &log_size));
			char *Log;
			Log = new char[log_size];
			glCheck(glGetProgramInfoLog(getGlId(), log_size, NULL, &Log[0]));
			fg_log<<"Error linking shader program: "<<Log<<std::endl;
			delete[] Log;
			return false;
		}

		glCheck(glValidateProgram(getGlId()));
		glCheck(glGetProgramiv(getGlId(), GL_VALIDATE_STATUS, &success));
		if (!success)
		{
			int log_size;
			glCheck(glGetProgramiv(getGlId(), GL_INFO_LOG_LENGTH, &log_size)); 
			char *Log;
			Log = new char[log_size];
			glCheck(glGetProgramInfoLog(getGlId(), log_size, NULL, &Log[0]));
			fg_log<<"Invalid shader program: "<<Log<<std::endl;
			delete[] Log;
			return false;
		}
		
		return true;
	}



	/// constructor /////////////////////////////////////////////////////////
	Shader::Shader() : m_texCount(0)
	{
		
	}


	/// destructor /////////////////////////////////////////////////////////
	Shader::~Shader()
	{
		if (glIsProgram(getGlId()))
		{
			C(m_subShaders.size())
				if (glIsShader(m_subShaders[i]))
					glCheck(glDetachShader(getGlId(),m_subShaders[i])),
					glCheck(glDeleteShader(m_subShaders[i]));
			glCheck(glDeleteProgram(getGlId()));
		}
	}


	/// functions /////////////////////////////////////////////////////////
	bool Shader::loadFromFiles(const std::string *files,const unsigned int *types,unsigned int count)
	{
		init();
		if (!getGlId())
		{
			fg_log<<"couldn't create shader program"<<std::endl;
			return false;
		}
		C(m_subShaders.size())
			if (glIsShader(m_subShaders[i]))
				glCheck(glDetachShader(getGlId(),m_subShaders[i])),
				glCheck(glDeleteShader(m_subShaders[i]));
				
		m_subShaders.resize(count);
		C(count)
		{
			m_subShaders[i] = compileSubShaderFromFile(files[i],types[i]);
			if (!m_subShaders[i])
				return false;
		}
			
		
		return link();
	}


	////////////////////////////////////////////////////////////
	bool Shader::loadFromMemory(const std::string *data,const unsigned int *types,unsigned int count)
	{
		init();
		if (!getGlId())
		{
			fg_log<<"couldn't create shader program"<<std::endl;
			return false;
		}
		C(m_subShaders.size())
			if (glIsShader(m_subShaders[i]))
				glCheck(glDetachShader(getGlId(),m_subShaders[i])),
				glCheck(glDeleteShader(m_subShaders[i]));
		
		m_subShaders.resize(count);
		C(count)
		{
			m_subShaders[i] = compileSubShader(data[i],types[i]);
			if (!m_subShaders[i])
				return false;
		}
		
		return link();
	}


	////////////////////////////////////////////////////////////
	bool Shader::loadFromFiles(const std::string &vertexShaderFile,const std::string &fragmentShaderFile)
	{
		if (vertexShaderFile == std::string())
		{
			if (fragmentShaderFile == std::string())
				return false;
			std::string files[] = {fragmentShaderFile};
			unsigned int types[] = {GL_FRAGMENT_SHADER};
			
			return loadFromFiles(files,types,1);
		}
		if (fragmentShaderFile == std::string())
		{
			std::string files[] = {vertexShaderFile};
			unsigned int types[] = {GL_VERTEX_SHADER};
			
			return loadFromFiles(files,types,1);
		}
		std::string files[] = {vertexShaderFile,fragmentShaderFile};
		unsigned int types[] = {GL_VERTEX_SHADER,GL_FRAGMENT_SHADER};
		
		return loadFromFiles(files,types,2);
	}


	////////////////////////////////////////////////////////////
	bool Shader::loadFromMemory(const std::string &vertexShaderFile,const std::string &fragmentShaderFile)
	{
		if (vertexShaderFile == std::string())
		{
			if (fragmentShaderFile == std::string())
				return false;
			std::string files[] = {fragmentShaderFile};
			unsigned int types[] = {GL_FRAGMENT_SHADER};
			
			return loadFromMemory(files,types,1);
		}
		if (fragmentShaderFile == std::string())
		{
			std::string files[] = {vertexShaderFile};
			unsigned int types[] = {GL_VERTEX_SHADER};
			
			return loadFromMemory(files,types,1);
		}
		std::string files[] = {vertexShaderFile,fragmentShaderFile};
		unsigned int types[] = {GL_VERTEX_SHADER,GL_FRAGMENT_SHADER};
		
		return loadFromMemory(files,types,2);
	}


	////////////////////////////////////////////////////////////
	void Shader::bind() const
	{
		glCheck(glUseProgram(getGlId()));
	}


	////////////////////////////////////////////////////////////
	void Shader::bind(const Shader *program)
	{
		if (program)
			program->bind();
		else glCheck(glUseProgram(0));
	}


	////////////////////////////////////////////////////////////
	void Shader::bind(const Shader &program)
	{
        program.bind();
	}


	////////////////////////////////////////////////////////////
	int Shader::getUniformLocation(const std::string &name)
	{
		if (!getGlId())
		{
			fg_log << "Error: trying to get location of \""<<name<<"\" uniform from unitialized shader" << std::endl;
			return -1;
		}
			
		std::map<std::string, int>::const_iterator it = m_uniforms.find(name);
		if (it != m_uniforms.end())
			return it->second;

		int location = glGetUniformLocation(getGlId(),name.c_str());

		if (location != -1)
			m_uniforms.insert(std::make_pair(name, location));
		else
			fg_log << "Couldn't find uniform "<<name<<" in shader."<<std::endl;

		return location;
	}


	////////////////////////////////////////////////////////////
	int Shader::getAttribLocation(const std::string &name)
	{
		if (!getGlId())
		{
			fg_log << "Error: trying to get location of \""<<name<<"\" attribute from unitialized shader" << std::endl;
			return -1;
		}
		
		std::map<std::string,int>::const_iterator it = m_attribs.find(name);
		if (it != m_attribs.end())
			return it->second;

		int location = glGetAttribLocation(getGlId(),name.c_str());

		if (location != -1)
			m_attribs.insert(std::make_pair(name,location)),
			glCheck(glEnableVertexAttribArray(location));
		else
			fg_log << "Couldn't find attribute "<<name<<" in shader."<<std::endl;

		return location;
	}

	#define CREATE_SET_UNIFORM(argList,callFunc)                       \
	Shader::reference Shader::setUniform argList                       \
	{                                                                  \
		if (getGlId())                                                 \
		{                                                              \
			int program;                                               \
			glCheck(glGetIntegerv(GL_CURRENT_PROGRAM,&program)); \
			glCheck(glUseProgram(getGlId()));                    \
                                                                       \
			int location = getUniformLocation(name);                   \
			if (location != -1)                                        \
				glCheck(callFunc);                                     \
                                                                       \
			glCheck(glUseProgram(program));                      \
		}                                                              \
		return *this;                                                  \
	}
	
	CREATE_SET_UNIFORM((const std::string &name,float x),glUniform1f(location,x))
	CREATE_SET_UNIFORM((const std::string &name,float x,float y),glUniform2f(location,x,y))
	CREATE_SET_UNIFORM((const std::string &name,float x,float y,float z),glUniform3f(location,x,y,z))
	CREATE_SET_UNIFORM((const std::string &name,float x,float y,float z,float w),glUniform4f(location,x,y,z,w))
	
	CREATE_SET_UNIFORM((const std::string &name,int x),glUniform1i(location,x))
	CREATE_SET_UNIFORM((const std::string &name,int x,int y),glUniform2i(location,x,y))
	CREATE_SET_UNIFORM((const std::string &name,int x,int y,int z),glUniform3i(location,x,y,z))
	CREATE_SET_UNIFORM((const std::string &name,int x,int y,int z,int w),glUniform4i(location,x,y,z,w))
	
	CREATE_SET_UNIFORM((const std::string &name,const fm::vec2 &v),glUniform2f(location,v.x,v.y))
	CREATE_SET_UNIFORM((const std::string &name,const fm::vec3 &v),glUniform3f(location,v.x,v.y,v.z))
	CREATE_SET_UNIFORM((const std::string &name,const fm::vec4 &v),glUniform4f(location,v.x,v.y,v.z,v.w))
	               
	////////////////////////////////////////////////////////////       
	Shader::reference Shader::setUniform(const std::string &name,const fm::mat3 &m,fm::MATRIX::StorageOrder storeOrder)
	{
		if (getGlId())
		{
			int program;
			glCheck(glGetIntegerv(GL_CURRENT_PROGRAM,&program));
			glCheck(glUseProgram(getGlId()));

			int location = getUniformLocation(name);
			if (location != -1)
			{
				if (storeOrder==fm::MATRIX::RowMajor)
					glCheck(glUniformMatrix3fv(location, 1, GL_FALSE, &(m.transpose())[0][0]));
				else
					glCheck(glUniformMatrix3fv(location, 1, GL_FALSE, &m[0][0]));
			}
			
			glCheck(glUseProgram(program));
		}
		return *this;
	}
	
	////////////////////////////////////////////////////////////       
	Shader::reference Shader::setUniform(const std::string &name,const fm::mat4 &m,fm::MATRIX::StorageOrder storeOrder)
	{
		if (getGlId())
		{
			int program;
			glCheck(glGetIntegerv(GL_CURRENT_PROGRAM,&program));
			glCheck(glUseProgram(getGlId()));

			int location = getUniformLocation(name);
			if (location != -1)
			{
				if (storeOrder==fm::MATRIX::RowMajor)
					glCheck(glUniformMatrix4fv(location, 1, GL_FALSE, &(m.transpose())[0][0]));
				else
					glCheck(glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]));
			}
			
			glCheck(glUseProgram(program));
		}
		return *this;
	}
	

	////////////////////////////////////////////////////////////
	Shader::reference Shader::setUniform(const std::string &name,const Texture &tex)
	{
		return setUniform(name,&tex);
	}


	////////////////////////////////////////////////////////////
	Shader::reference Shader::setUniform(const std::string &name,const Texture *tex)
	{
		if (getGlId())
		{
			int program;
			glCheck(glGetIntegerv(GL_CURRENT_PROGRAM,&program));
			glCheck(glUseProgram(getGlId()));

			std::map<std::string, TexUniformData >::iterator it = m_textures.find(name);
			if (it != m_textures.end())
			{
				glCheck(glActiveTexture(GL_TEXTURE0+it->second.slot));
				glCheck(glBindTexture(GL_TEXTURE_2D,tex ? tex->getGlId() : 0));
				it->second.act_id = tex ? tex->getGlId() : 0;
			}
			else
			{
				int location = glGetUniformLocation(getGlId(),name.c_str());

				if (location != -1)
				{
					m_textures.insert(std::make_pair(name, TexUniformData(location,m_texCount,tex ? tex->getGlId() : 0)));
					glCheck(glUniform1i(location, m_texCount));
					glCheck(glActiveTexture(GL_TEXTURE0+m_texCount));
					glCheck(glBindTexture(GL_TEXTURE_2D,tex ? tex->getGlId() : 0));
					m_texCount++;
				}
				else
					fg_log << "Couldn't find texture "<<name<<" in shader."<<std::endl;

				glCheck(glActiveTexture(GL_TEXTURE0));
				glCheck(glUseProgram(program));

			}
		}
		return *this;
	}


	////////////////////////////////////////////////////////////
    Shader::reference Shader::setAttribPointer(const std::string &name,unsigned int dimensions,unsigned long type,bool normalize,const void *pointer,unsigned int stride)
    {
		if (getGlId())
		{
			int location = getAttribLocation(name);
			
			if (location!=-1)
				glCheck(glVertexAttribPointer(location,dimensions,type,normalize,stride,pointer));			
		}
		return *this;
    }

	////////////////////////////////////////////////////////////
    bool Shader::isAvailable()
    {
    	#ifdef GL_SHADING_LANGUAGE_VERSION
        	std::string glslVer = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
        	if (glGetError() != GL_NO_ERROR)
        		return false;
        	return (glslVer.size()>0);
        #else
        	return false;
        #endif
    }
}