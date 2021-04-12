#include "enigme.h"



void generer_enigme(enigme *e){
	e->pos_selected=0;
	e->background= IMG_Load("img/background.png");
	e->button= IMG_Load("img/button.png");
	e->button_s= IMG_Load("img/button_s.png");

	TTF_Init();
	TTF_Font *police = NULL,*police1=NULL;

	SDL_Color couleur = {0,0,0};

	police = TTF_OpenFont("arial.ttf", 30);
	police1 = TTF_OpenFont("arial.ttf", 20);
	SDL_Surface *texte;

	char questionn[50];

	srand(time(NULL));
	e->num_question=rand()%4;

	while(e->num_question==0){
		srand(time(NULL));
		e->num_question=rand()%4;
	}

	FILE *fquestion=NULL;
	fquestion=fopen("questions.txt","r+");
	if(fquestion!=NULL){
		int test=1;
		while (fgets(questionn, 50, fquestion) &&(test!=e->num_question)){
			test++;
		}
		
		fclose(fquestion);
	}

	char reponse[20],reponse1[20],reponse2[20],reponse3[20];

	int min,max;
    switch(e->num_question)
    {
    	case 1:
    	{
    		min=0;
    		max=2;
    		break;
    	}
    	case 2:
    	{
    		min=3;
    		max=5;
    		break;
    	}
    	case 3:
    	{
    		min=6;
    		max=8;
    		break;
    	}
    }

	FILE *freponse=NULL;
	freponse=fopen("reponses.txt","r+");
	if(freponse!=NULL){
		int test=0;
		while (fgets((reponse), 15, freponse) &&(test<max)){
			
			printf("%s\n",reponse);
			if(test>=min){
				e->reponses[test-min]=TTF_RenderText_Blended(police1, reponse, couleur);
			}
			test++;
		}	
		fclose(freponse);
	}


	FILE *fvraireponse=NULL;
	fvraireponse=fopen("vraireponses.txt","r+");
	if(fvraireponse!=NULL){
		int test=1;
		while (fgets((reponse), 15, fvraireponse)){
			
			if(test==e->num_question){
				e->reponses[2]=TTF_RenderText_Blended(police1, reponse, couleur);
				e->positionVraiReponse=3;
			}
			test++;
		}
		fclose(freponse);
	}


	e->question = TTF_RenderText_Blended(police, questionn, couleur);

	e->pos_question.x=270;
	e->pos_question.y=270;

	e->pos_reponse1.x=375;
	e->pos_reponse1.y=522;

	e->pos_reponse2.x=177;
	e->pos_reponse2.y=648;

	e->pos_reponse3.x=566;
	e->pos_reponse3.y=651;

	e->pos_reponse1txt.x=375+50;
	e->pos_reponse1txt.y=522+30;

	e->pos_reponse2txt.x=177+50;
	e->pos_reponse2txt.y=648+30;

	e->pos_reponse3txt.x=566+50;
	e->pos_reponse3txt.y=651+30;
}

void afficher_enigme(enigme *e,SDL_Surface *ecran){

	SDL_BlitSurface(e->background, NULL, ecran, NULL);
	SDL_Flip(ecran);
	SDL_BlitSurface(e->question, NULL, ecran, &e->pos_question);
	SDL_Flip(ecran);

	switch(e->pos_selected){
		case 1:
		{
			SDL_BlitSurface(e->button_s, NULL, ecran, &e->pos_reponse1);
			SDL_Flip(ecran);
			SDL_BlitSurface(e->button, NULL, ecran, &e->pos_reponse2);
			SDL_Flip(ecran);
			SDL_BlitSurface(e->button, NULL, ecran, &e->pos_reponse3);
			SDL_Flip(ecran);

			SDL_BlitSurface(e->reponses[0], NULL, ecran, &e->pos_reponse1txt);
			SDL_Flip(ecran);
			SDL_BlitSurface(e->reponses[1], NULL, ecran, &e->pos_reponse2txt);
			SDL_Flip(ecran);
			SDL_BlitSurface(e->reponses[2], NULL, ecran, &e->pos_reponse3txt);
			SDL_Flip(ecran);

		}
		break;
		case 2:
		{
			SDL_BlitSurface(e->button, NULL, ecran, &e->pos_reponse1);
			SDL_Flip(ecran);
			SDL_BlitSurface(e->button_s, NULL, ecran, &e->pos_reponse2);
			SDL_Flip(ecran);
			SDL_BlitSurface(e->button, NULL, ecran, &e->pos_reponse3);
			SDL_Flip(ecran);

			SDL_BlitSurface(e->reponses[0], NULL, ecran, &e->pos_reponse1txt);
			SDL_Flip(ecran);
			SDL_BlitSurface(e->reponses[1], NULL, ecran, &e->pos_reponse2txt);
			SDL_Flip(ecran);
			SDL_BlitSurface(e->reponses[2], NULL, ecran, &e->pos_reponse3txt);
			SDL_Flip(ecran);

		}
		break;
		case 3:
		{
			SDL_BlitSurface(e->button, NULL, ecran, &e->pos_reponse1);
			SDL_Flip(ecran);
			SDL_BlitSurface(e->button, NULL, ecran, &e->pos_reponse2);
			SDL_Flip(ecran);
			SDL_BlitSurface(e->button_s, NULL, ecran, &e->pos_reponse3);
			SDL_Flip(ecran);

			SDL_BlitSurface(e->reponses[0], NULL, ecran, &e->pos_reponse1txt);
			SDL_Flip(ecran);
			SDL_BlitSurface(e->reponses[1], NULL, ecran, &e->pos_reponse2txt);
			SDL_Flip(ecran);
			SDL_BlitSurface(e->reponses[2], NULL, ecran, &e->pos_reponse3txt);
			SDL_Flip(ecran);
		}
		break;
		default:
		{
			SDL_BlitSurface(e->button, NULL, ecran, &e->pos_reponse1);
			SDL_Flip(ecran);
			SDL_BlitSurface(e->button, NULL, ecran, &e->pos_reponse2);
			SDL_Flip(ecran);
			SDL_BlitSurface(e->button, NULL, ecran, &e->pos_reponse3);
			SDL_Flip(ecran);

			SDL_BlitSurface(e->reponses[0], NULL, ecran, &e->pos_reponse1txt);
			SDL_Flip(ecran);
			SDL_BlitSurface(e->reponses[1], NULL, ecran, &e->pos_reponse2txt);
			SDL_Flip(ecran);
			SDL_BlitSurface(e->reponses[2], NULL, ecran, &e->pos_reponse3txt);
			SDL_Flip(ecran);
		}
	}
	SDL_Delay(100);
}

void free_enigme(enigme *e){
	SDL_FreeSurface(e->background);
	SDL_FreeSurface(e->question);
	SDL_FreeSurface(e->reponses[0]);
	SDL_FreeSurface(e->reponses[1]);
	SDL_FreeSurface(e->reponses[2]);
	SDL_FreeSurface(e->button);
	SDL_FreeSurface(e->button_s);
}

void verify_enigme(enigme *e)
{
	if(e->positionVraiReponse==e->pos_selected)
	{
		printf("You win\n");
	}
	else
	{
		printf("You lost\n");
	}
}