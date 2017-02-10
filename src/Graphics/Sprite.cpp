#include <FRONTIER/Graphics/ShaderManager.hpp>
#include <FRONTIER/Graphics/Attribute.hpp>
#include <FRONTIER/Graphics/Texture.hpp>
#include <FRONTIER/Graphics/Sprite.hpp>
#include <FRONTIER/Graphics/Glyph.hpp>

namespace fg
{
    /////////////////////////////////////////////////////////////
    Sprite::Sprite() : m_tex(nullptr)
    {
		
    }
    
    /////////////////////////////////////////////////////////////
	Sprite::Sprite(const Glyph &glyph) : m_tex(glyph.tex),
										 m_texRect(glyph.pos,glyph.size),
										 m_size(glyph.size)
    {
		init();
    }
    
    /////////////////////////////////////////////////////////////
    Sprite::Sprite(fm::Ref<const fg::Texture> tex) : m_tex(tex),
													 m_texRect(tex ? fm::rect2s(fm::vec2s(),tex->getSize()) : fm::rect2s()),
													 m_size(tex ? tex->getSize() : fm::vec2())
    {
		init();
    }
    
    /////////////////////////////////////////////////////////////
    Sprite::Sprite(fm::Ref<const fg::Texture> tex,
                   const fm::rect2s &texRect) : m_tex(tex),
												m_texRect(texRect),
												m_size(texRect.size),
												m_pos(texRect.pos)
    {
        init();
    }
    
    /////////////////////////////////////////////////////////////
    Sprite::Sprite(fm::Ref<const fg::Texture> tex,
                   const fm::rect2s &texRect,
                   const fm::vec2 &pos,
                   const fm::vec2 &size) : m_tex(tex),
										   m_texRect(texRect),
										   m_size(size),
										   m_pos(pos)
    {
        init();
    }

    /////////////////////////////////////////////////////////////
    void Sprite::init()
    {
		if (!m_tex) return;

		if (m_draw.getDrawCount() == 0)
        {
            fm::vec2 pts[] = {fm::vec2(0,0),fm::vec2(1,0),fm::vec2(1,1),fm::vec2(0,1)};
            fm::vec4 clr[] = {fm::vec4::White,fm::vec4::White,fm::vec4::White,fm::vec4::White};

            m_draw[fg::Assoc::Position]  = pts;
            m_draw[fg::Assoc::TextureUV] = pts;
            m_draw[fg::Assoc::Color]     = clr;

            m_draw.addDraw(0,4,fg::TriangleFan);
        }
    }

    /////////////////////////////////////////////////////////////
    Sprite &Sprite::setPos(const fm::vec2 &pos)
    {
        init();
        m_pos = pos;
        return *this;
    }

    const fm::vec2 &Sprite::getPos() const
    {
        return m_pos;
    }


    /////////////////////////////////////////////////////////////
    Sprite &Sprite::setSize(const fm::vec2 &size)
    {
        init();
        m_size = size;
        return *this;
    }

    const fm::vec2 &Sprite::getSize() const
    {
        return m_size;
    }


    /////////////////////////////////////////////////////////////
    Sprite &Sprite::setTexRect(const fm::rect2s &texRect)
    {
        init();
        m_texRect = texRect;
        return *this;
    }

    const fm::rect2s &Sprite::getTexRect() const
    {
        return m_texRect;
    }

    /////////////////////////////////////////////////////////////
    Sprite &Sprite::setTexture(fm::Ref<const fg::Texture> tex)
    {
        m_tex = tex;
        return *this;
    }

    /////////////////////////////////////////////////////////////
    Sprite &Sprite::setTexture(fm::Ref<const fg::Texture> tex,const fm::rect2s &texRect)
    {
        m_tex = tex;
        setTexRect(texRect);
        return *this;
    }

    const fg::Texture *Sprite::getTexture() const
    {
        return m_tex;
    }


    /////////////////////////////////////////////////////////////
    void Sprite::onDraw(ShaderManager &shader)
	{
        if (!m_tex) return;

        shader.getModelStack().push().mul(fm::MATRIX::translation(fm::vec2(fm::vec2i(m_pos)))*fm::MATRIX::scaling(fm::vec2(fm::vec2i(m_size))));
        shader.getTexUVStack().push().mul(m_tex->getPixToUnitMatrix()*fm::MATRIX::translation((fm::vec2)m_texRect.pos)*fm::MATRIX::scaling((fm::vec2)m_texRect.size));
        shader.useTexture(m_tex);
        shader.draw(m_draw);
        shader.useTexture(nullptr);
        shader.getModelStack().pop();
        shader.getTexUVStack().pop();
    }


    /////////////////////////////////////////////////////////////
    void Sprite::onUpdate(const fm::Time &dt)
    {
        (void)dt;
    }
}
