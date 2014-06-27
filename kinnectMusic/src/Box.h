#pragma once
#include "ofRectangle.h"
#include "ofTexture.h"

class Box: public ofRectangle
{
public:
	Box(void);
	virtual~Box(void);
public:
	void SetisVisible(){m_Visibility = true;}
	void SetisNotvisible(){m_Visibility = false;}
	void SetColor(int r, int g, int b){m_Color.x = r, m_Color.y = g, m_Color.z = b;}

	void Draw();
	void GlDraw(ofTexture texture);

private:
	bool m_Visibility;
	ofPoint m_Color;
};

