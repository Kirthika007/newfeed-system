#include <gtk/gtk.h>
#include "graph.h"
#include "heap.h"

#define MAX_ARTICLES 100

typedef struct {
    char title[100];
    char topic[50];
    int score;
} NewsArticle;

NewsArticle articles[MAX_ARTICLES];
int article_count = 0;

void load_data() {
    FILE *news_file = fopen("data/news.txt", "r");
    while (fscanf(news_file, "%[^,],%[^,],%d\n", 
                 articles[article_count].title,
                 articles[article_count].topic,
                 &articles[article_count].score) != EOF) {
        article_count++;
    }
    fclose(news_file);
}

void refresh_feed(GtkWidget *label) {
    int scores[MAX_ARTICLES];
    for (int i = 0; i < article_count; i++) {
        scores[i] = articles[i].score;
    }
    buildHeap(scores, article_count);

    char feed[2000] = "📰 Your Personalized Feed:\n\n";
    for (int i = 0; i < 5 && i < article_count; i++) {
        char line[200];
        snprintf(line, sizeof(line), "%d. %s (%s) - Score: %d\n\n",
                i+1, articles[i].title, articles[i].topic, articles[i].score);
        strcat(feed, line);
    }
    gtk_label_set_text(GTK_LABEL(label), feed);
}

void on_refresh(GtkWidget *widget, gpointer data) {
    refresh_feed(GTK_WIDGET(data));
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    load_data();

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "News Feed");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *label = gtk_label_new("Press refresh to load articles");
    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
    
    GtkWidget *button = gtk_button_new_with_label("🔄 Refresh");
    g_signal_connect(button, "clicked", G_CALLBACK(on_refresh), label);

    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
