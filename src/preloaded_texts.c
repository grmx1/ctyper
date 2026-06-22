#include "preloaded_texts.h"

char* texts[TEXTS_SIZE] = {

	"Typists often handle confidential documents. Treat sensitive information with the utmost care. Follow company policies regarding data security and privacy. Securely store or destroy confidential documents as instructed.\0",

	"There are many idiosyncratic typing styles in between novice-style \"hunt and peck\" and touch typing. For example, many \"hunt and peck\" typists have the keyboard layout memorized and are able to type while focusing their gaze on the screen. Some use just two fingers, while others use 3-6 fingers. Some use their fingers very consistently, with the same finger being used to type the same character every time, while others vary the way they use their fingers.\0",

	"Failure is not the end; it's a detour on the road to success. Everyone stumbles and falls along the way, but what truly matters is how you respond. Instead of letting setbacks discourage you, view them as valuable learning experiences. Analyze what went wrong, extract the lessons, adjust your approach, and keep moving forward with renewed determination. Remember, every successful person has encountered failure at some point. It's through these challenges that we grow stronger, wiser, and more resilient.\0",

	"Fast and accurate typing opens doors to various career paths. Administrative assistants, legal secretaries, and data entry specialists rely heavily on their typing skills. Transcriptionists convert audio recordings into written documents, making strong typing abilities essential. Writers, editors, and journalists utilize typing to create and revise their work efficiently. In the digital age, content creators, social media managers, and customer service representatives depend on typing to communicate effectively online.\0",

	"Accountability is a critical component of teamwork. Each team member must take responsibility for their actions, their contributions, and their impact on the team's overall performance. When everyone is accountable, the team can function smoothly, with everyone pulling their weight and working towards a common goal. Accountability also fosters trust, as team members know that they can rely on each other to fulfill their commitments.\0",

	"After graduating with a degree in graphic design, Emily landed a 3-month internship at a prestigious advertising agency. She quickly impressed her colleagues with her creativity and work ethic, often staying late to perfect her designs. By the end of the internship, Emily had not only gained valuable experience but also secured a full-time job offer, proving that internships can be a stepping stone to career success.\0",

	"Learning keyboard shortcuts for common commands can significantly improve your typing efficiency. Practice using shortcuts for actions like copying, pasting, saving, and formatting text. Over time, these shortcuts will become second nature and save you valuable time.\0",

	"Well-formatted documents reflect professionalism and attention to detail. Use appropriate fonts, margins, and line spacing for readability. Create clear headings and subheadings to organize information. Utilize lists and tables to present data effectively.\0",

	"Efficient filing systems are the backbone of an organized office. Choose a system that suits your company's needs, whether it's alphabetical, numerical, or subject-based. Clearly label files and folders for easy retrieval. Regularly purge outdated documents to avoid clutter. Embrace digital filing solutions to streamline storage and access to information. Back up important files regularly to prevent data loss.\0",

	"Business casual is an ambiguously defined dress code that has been adopted by many professional and white-collar workplaces in Western countries. It entails neat yet casual attire and is generally more casual than informal attire but more formal than casual or smart casual attire. Casual Fridays preceded widespread acceptance of business casual attire in many offices.\0"

};

char* get_random_text(size_t* bsize){

	srand(time(NULL));

	int index = rand() % TEXTS_SIZE;

	*bsize = 0;
	int counter = 0;
	int c = 0;

	do{

		c = texts[index][counter++];
	}while(c != 0);

	*bsize = counter;

	return texts[index];
}
