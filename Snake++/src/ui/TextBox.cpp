#include "TextBox.h"

TextBox::TextBox()
{
	this->setup(5, 9, 200, sf::Vector2f(0, 0));
}

TextBox::TextBox(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos)
{
	this->setup(l_visible, l_charSize, l_width, l_screenPos);
}

TextBox::~TextBox()
{
	this->clear();
}

void TextBox::setup(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos)
{
	this->m_numVisible = l_visible;
	sf::Vector2f l_offset(2.0f, 2.0f);
	this->m_font.loadFromFile("assets/fonts/arial.ttf");
	this->m_content.setFont(this->m_font);
	this->m_content.setString("");
	this->m_content.setCharacterSize(l_charSize);
	this->m_content.setFillColor(sf::Color::White);
	this->m_content.setOutlineColor(sf::Color::Black);
	this->m_content.setPosition(l_screenPos + l_offset);
	this->m_backdrop.setSize(sf::Vector2f(l_width, (l_visible * (l_charSize * 1.2f))));
	this->m_backdrop.setFillColor(sf::Color(90, 90, 90, 90));
	this->m_backdrop.setPosition(l_screenPos);
}

void TextBox::add(std::string l_message)
{
	this->m_messages.push_back(l_message);
	if (this->m_messages.size() < 6) {
		return;
	}
	this->m_messages.erase(this->m_messages.begin());
}

void TextBox::clear()
{
	this->m_messages.clear();
}

void TextBox::render(sf::RenderWindow& l_window)
{
	std::string l_content;
	for (auto& itr : this->m_messages) 
	{
		l_content.append(itr + "\n");
	}

	if (l_content != "")
	{
		this->m_content.setString(l_content);
		l_window.draw(this->m_backdrop);
		l_window.draw(this->m_content);
	}

}
