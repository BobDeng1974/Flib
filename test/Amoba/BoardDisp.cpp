#include "BoardDisp.hpp"

BoardDisp::BoardDisp(GuiContext &cont, int size) : Widget(cont, cont.getSize()),
	m_size(size)
{
	makeProps();
	prepareDDs();
	
	onresize = [&](vec2 s){
		setSize(s);
		makeProps();
		prepareDDs();
	};
}

void BoardDisp::makeProps()
{
	props.N    = m_size;
	props.mid  = getSize()/2;
	props.siz  = getSize().min();
	props.base = props.mid - vec2(props.siz)/2;
	props.gsz  = props.siz/props.N;
}

void BoardDisp::prepareDDs()
{
	float xin = .08;
	vec4 gclr = vec4(.5);
	vec4 oclr = vec4(.8,.6,.5);
	vec4 xclr = vec4(.5,.6,.8);
	
	Mesh m;
	for (int i=0;i<=props.N;++i) {
		m.pts.push_back(props.base + vec2(props.gsz*i,0));
		m.pts.push_back(props.base + vec2(props.gsz*i,props.siz));
		m.pts.push_back(props.base + vec2(0,props.gsz*i));
		m.pts.push_back(props.base + vec2(props.siz,props.gsz*i));
	}
	
	m.clr.resize(m.pts.size(),gclr);
	
	m_grid = m;
	m_grid.clearDraws();
	m_grid.addDraw(fg::Lines);
	
	float xins = xin/sqrt(2)*props.gsz;
	Mesh mx;
	mx.pts.push_back(vec2(0,xins));
	mx.pts.push_back(vec2(xins,0));
	mx.pts.push_back(vec2(props.gsz,props.gsz-xins));
	mx.pts.push_back(vec2(0,xins));
	mx.pts.push_back(vec2(props.gsz,props.gsz-xins));
	mx.pts.push_back(vec2(props.gsz-xins,props.gsz));
	
	mx.pts.push_back(vec2(props.gsz,xins));
	mx.pts.push_back(vec2(props.gsz-xins,0));
	mx.pts.push_back(vec2(0,props.gsz-xins));
	mx.pts.push_back(vec2(props.gsz,xins));
	mx.pts.push_back(vec2(0,props.gsz-xins));
	mx.pts.push_back(vec2(xins,props.gsz));
	
	mx.clr.resize(mx.pts.size(),xclr);
	
	m_X = mx;
	
	
	
	float oins = xin*props.gsz;
	Mesh mo;
	
	vector<vec2> lineo;
	int ko = 30;
	for (int i=0;i<ko;++i) {
		vec2 p = vec2(props.gsz/2) + vec2(pol2(props.gsz/2-oins/2,deg(i/(ko-1.f)*360)));
		lineo.push_back(p);
	}
	
	mo = Mesh::tesLineStrip(&lineo[0],lineo.size(),oins);
	
	mo.clr.resize(mo.pts.size(),oclr);
	
	m_O = mo;
}
	
void BoardDisp::onDraw(fg::ShaderManager &shader)
{
	shader.draw(m_grid);
	
	shader.getModelStack().push();
	for (auto &s : m_moves) {
		DrawData &dd = (s.z == 1 ? m_X : m_O);
		
		shader.getModelStack().top(MATRIX::translation(props.base + vec2(s)*props.gsz));
		shader.draw(dd);
	}
	shader.getModelStack().pop();
}
	
void BoardDisp::addStep(vec2i p,int id)
{
	m_moves.push_back(vec3i(p,id));
}

void BoardDisp::remStep(bool all)
{
	if (all) m_moves.clear();
	else if (!m_moves.empty())
		m_moves.pop_back();
}
