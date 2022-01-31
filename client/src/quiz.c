#include "quiz.h"

int *get_array_of_diff_rand(int size) {
    int *elements = malloc(sizeof(int)*size);

    for (int i = 0; i < size; ++i)
        elements[i] = i;

    for (int i = size - 1; i > 0; --i) {
      int w = rand()%i;
      int t = elements[i];
    elements[i] = elements[w];
    elements[w] = t;
    }
    return elements;
}
    
gboolean answer_clicked(GtkWidget *widget, t_quiz_info *quiz_info) {

    // send user answer on server

    // if(!strcmp((char*)gtk_button_get_label(GTK_BUTTON(widget)), quiz_info->correct_answer)) {
    //     gtk_popover_popdown(GTK_POPOVER(quiz_info->quiz_popover));
    // } else {
    //     // notify user that the answer is wrong
    //     // place_answer_error(widget);
    // }

    cJSON* response = check_answer_request(get_cookies(), (char*)gtk_button_get_label(GTK_BUTTON(widget)));

    char* result = get_from_protocol_string(response, "DATA");

    if (strcmp(result, "CORRECT") == 0) {
        gtk_popover_popdown(GTK_POPOVER(quiz_info->quiz_popover));
        printf("correct answer\n");
    } else {
        // change answer
        printf("incorrect answer\n");
    }

    return true;
}

// TODO: add show quiz function

gboolean quiz_button_clicked(GtkWidget *widget, t_quiz_info *quiz_info) {
    if(widget) {

        // get question from server

        // random question = get question from server

        cJSON* response = get_question_request(get_cookies());
        cJSON* random_question = cJSON_Parse(get_from_protocol_string(response, "DATA"));

        char*  question_index = get_from_protocol_string(response, "QUESTION INDEX");
        if (get_from_protocol_string(get_cookies(), "QUESTION INDEX")) cJSON_DeleteItemFromObject(get_cookies(), "QUESTION INDEX");
        add_to_protocol_string(get_cookies(), "QUESTION INDEX", question_index);

        GtkWidget *question_label = GTK_WIDGET(gtk_builder_get_object(quiz_info->builder, "quiz_label"));
        GtkWidget *answer_buttons[4];
        answer_buttons[0] = GTK_WIDGET(gtk_builder_get_object(quiz_info->builder, "answer_button_1"));
        answer_buttons[1] = GTK_WIDGET(gtk_builder_get_object(quiz_info->builder, "answer_button_2"));
        answer_buttons[2] = GTK_WIDGET(gtk_builder_get_object(quiz_info->builder, "answer_button_3"));
        answer_buttons[3] = GTK_WIDGET(gtk_builder_get_object(quiz_info->builder, "answer_button_4"));

        if(quiz_info->pop_opened == 0) {
            char *correct_answer = get_from_protocol_string(random_question, "CORRECT_ANSWER");
            quiz_info->correct_answer = correct_answer;

            int *rand_arr = get_array_of_diff_rand(4);
            gtk_label_set_text(GTK_LABEL(question_label), get_from_protocol_string(random_question, "QUESTION"));
            gtk_button_set_label(GTK_BUTTON(answer_buttons[rand_arr[0]]), get_from_protocol_string(random_question, "ANSWER_1"));
            gtk_button_set_label(GTK_BUTTON(answer_buttons[rand_arr[1]]), get_from_protocol_string(random_question, "ANSWER_2"));
            gtk_button_set_label(GTK_BUTTON(answer_buttons[rand_arr[2]]), get_from_protocol_string(random_question, "ANSWER_3"));
            gtk_button_set_label(GTK_BUTTON(answer_buttons[rand_arr[3]]), correct_answer);

            g_signal_connect (G_OBJECT (answer_buttons[0]), "clicked", G_CALLBACK (answer_clicked), quiz_info);
            g_signal_connect (G_OBJECT (answer_buttons[1]), "clicked", G_CALLBACK (answer_clicked), quiz_info);
            g_signal_connect (G_OBJECT (answer_buttons[2]), "clicked", G_CALLBACK (answer_clicked), quiz_info);
            g_signal_connect (G_OBJECT (answer_buttons[3]), "clicked", G_CALLBACK (answer_clicked), quiz_info);


            quiz_info->pop_opened = 1;
        } else {
            quiz_info->pop_opened = 0;
        }

        cJSON_Delete(response);
    } else {
        quiz_info->pop_opened = 1;
    }
    return true;
}




// int set_quiz_from_file(cJSON **questions_arr, char *file_name) {
//     char *file = mx_file_to_str(file_name);
//     char** questions = mx_strsplit(file, '\n');
//     *questions_arr = cJSON_CreateObject();
//     int questions_number = 0;

//     for(questions_number = 0; questions[questions_number] != NULL; questions_number++) {
//         cJSON* question = cJSON_CreateObject();
//         char **question_info = mx_strsplit(questions[questions_number], ';');

//         add_to_protocol_string(question, "QUESTION", question_info[0]);
//         add_to_protocol_string(question, "CORRECT_ANSWER", question_info[1]);
//         add_to_protocol_string(question, "ANSWER_1", question_info[2]);
//         add_to_protocol_string(question, "ANSWER_2", question_info[3]);
//         add_to_protocol_string(question, "ANSWER_3", question_info[4]);

//         add_to_protocol(*questions_arr, mx_itoa(questions_number), question);

//         mx_del_strarr(&question_info);
//     }
//     return questions_number;
// }

void set_quiz_on_button(GtkWidget *button) {

    cJSON *quiz_questions;
    // int questions_number = set_quiz_from_file(&quiz_questions, "quiz");

    // printf("%s\n", cJSON_Print(quiz_questions));

    gtk_button_set_image (GTK_BUTTON (button), gtk_image_new_from_icon_name ("open-menu-symbolic", GTK_ICON_SIZE_BUTTON));

    GtkWidget *quiz_popover;
    GtkBuilder *builder = gtk_builder_new_from_file(get_path_to_glade("quiz.glade"));
	GtkWidget *quiz_layout = GTK_WIDGET(gtk_builder_get_object(builder, "quiz_layout"));
	
    quiz_popover = gtk_popover_new (button);
    gtk_container_add (GTK_CONTAINER (quiz_popover), quiz_layout);
    gtk_menu_button_set_popover (GTK_MENU_BUTTON (button), quiz_popover);


    t_quiz_info *quiz_info = (t_quiz_info *)malloc(sizeof(t_quiz_info));
    
    quiz_info->pop_opened = 0;
    quiz_info->quiz_popover = quiz_popover;
    quiz_info->builder = builder;
    quiz_info->questions = quiz_questions;
    // quiz_info->quiz_quiestions_number = questions_number;

    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (quiz_button_clicked), quiz_info);

}
