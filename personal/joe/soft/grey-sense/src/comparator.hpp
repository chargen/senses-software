#pragma once
#include <letter.hpp>
#include <bitmap.h>
#include <greyscale.h>
#include <vector>
#include <cstdio>

class Comparator {
	unsigned int get_supremum(std::vector<float>);
	std::string typeface;
	std::vector<Letter> templates;
public:
	Comparator(void);
	void load_templates(std::string, bool);
	Letter greyscale2letter(GREYSCALE*);
	char identify(Letter, bool);
	std::vector<Letter> get_templates(bool);
};

Letter Comparator::greyscale2letter(GREYSCALE *greyscale)
{
	Letter letter;

	letter.set_pattern(greyscale->table);

	return letter;
}

unsigned int Comparator::get_supremum(std::vector<float> vec)
{
	float max_score = 0;
	unsigned int out = 0;

	for (unsigned int i = 0; i < vec.size(); ++i)
	{
		if (vec[i] > max_score) {
			max_score = vec[i];
			out = i;
		}
	}

	return out;
}

void Comparator::load_templates(std::string src = "templates/std", bool debug_me = false)
{
	char path[256];

	typeface = src;
	for (int i = 0; i < 10; ++i)
	{
		sprintf(path, "%s/%d.bmp", src.c_str(), i);
		templates.push_back(greyscale2letter(greyscale_load(path)));
		templates[i].set_id('0' + i);
		if (debug_me) templates[i].write();
	}
}

Comparator::Comparator(void)
{
	return;
}

char Comparator::identify(Letter to_find, bool debug_me = false)
{
	std::vector<Letter>::iterator it;
	std::vector<float> score;

	for (it = templates.begin(); it != templates.end(); ++it)
		score.push_back(to_find.compare(*it));

	if (debug_me == true) {
		printf("---\n");
		for (unsigned int i = 0; i < templates.size(); ++i)
		{
			printf("%c: %.2f\n", templates[i].get_id(), score[i]);
		}
	}

	return templates[get_supremum(score)].get_id();
}

std::vector<Letter> Comparator::get_templates(bool debug_me = false)
{
	return templates;
}
