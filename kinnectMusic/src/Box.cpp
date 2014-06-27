#include "Box.h"
#include "ofGraphics.h"


Box::Box(void):
	m_Visibility(true)
{
}


Box::~Box(void)
{
}


void Box::Draw()
{
	if (false != m_Visibility)
	{
		ofNoFill();
		ofSetColor(m_Color.x,m_Color.y,m_Color.z);
		ofRect(position.x, position.y, width, height);
	}
}

void Box::GlDraw(ofTexture texture)
{
	if (false != m_Visibility)
	{
		ofPoint x(getMinX(),getMinY()); 
		ofPoint y(getMaxX(),getMinY());
		ofPoint z(getMaxX(), getMaxY());
		ofPoint a(getMinX(), getMaxY());

		ofSetColor(m_Color.x=255,m_Color.y=255,m_Color.z=255);
		glBegin(GL_QUADS);
		glVertex2f(x.x, x.y);
		glVertex2f(y.x, y.y);
		glVertex2f(z.x, z.y);
		glVertex2f(a.x, a.y);
		glEnd();

		texture.draw(x,y,z,a);

	}
}
