#include <gtk/gtk.h>
#include <stdlib.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdio.h>

void zoomin(GtkWidget *pWidget, gpointer data);
void zoomout(GtkWidget *pWidget, gpointer data);


int main(int argc, char **argv)
{
        /*initialiser la gtk*/
        gtk_init(&argc,&argv);

        /*---------------  Variables  ----------------*/
        GtkWidget *pWindow;
        GtkWidget *pVbox, *pHbox;
        GtkWidget *zoom_in, *zoom_out, *Quitter;
        GtkWidget *Image;
        GtkWidget * scroll;
        
         GdkPixbuf *buf;


        /*-------------------fenetre------------------*/

        pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        //position de la fentre
        gtk_window_set_position(GTK_WINDOW(pWindow),GTK_WIN_POS_CENTER);
        //titre de la fentre
        gtk_window_set_title(GTK_WINDOW(pWindow),"titre temporaire de la fentre");
        //taille de la fenetre  width x height
        gtk_window_set_default_size(GTK_WINDOW(pWindow), 900,800);
        //signal pour detruire la fentre 
        g_signal_connect(G_OBJECT(pWindow),"destroy",G_CALLBACK(gtk_main_quit),NULL);
       
        
        
        /*----------------   Image   --------------------*/
     //   Image = gtk_image_new_from_file("bourges.jpeg");
        buf = gdk_pixbuf_new_from_file_at_size("4k.jpg",880,800,NULL);
        Image = gtk_image_new_from_pixbuf(buf);

        
        /*-------------------   boutton   --------------------*/
        zoom_in = gtk_button_new_with_label("Zoom IN");
        zoom_out = gtk_button_new_with_label("Zoom Out");
        Quitter = gtk_button_new_with_mnemonic("_Quitter");
        g_signal_connect(G_OBJECT(Quitter),"clicked",G_CALLBACK(gtk_main_quit),NULL);
        g_signal_connect(G_OBJECT(zoom_in),"clicked",G_CALLBACK(zoomin),Image);
        g_signal_connect(G_OBJECT(zoom_out),"clicked",G_CALLBACK(zoomout),Image);
       
        /*----------   boite   -----------*/
        pVbox = gtk_vbox_new(FALSE,5);
        gtk_container_add(GTK_CONTAINER(pWindow),pVbox);


    //    gtk_box_pack_start(GTK_BOX(pVbox),Image,TRUE,FALSE,0);

        pHbox = gtk_hbox_new(TRUE,5);
        gtk_box_pack_start(GTK_BOX(pVbox),pHbox,FALSE,FALSE,5);

        gtk_box_pack_start(GTK_BOX(pHbox),zoom_in,TRUE,TRUE,0);
        gtk_box_pack_start(GTK_BOX(pHbox),zoom_out,TRUE,TRUE,0);
        gtk_box_pack_start(GTK_BOX(pHbox),Quitter,TRUE,TRUE,0);

        
        /*--------------barre de defilment ----------------*/
        scroll = gtk_scrolled_window_new(NULL,NULL);
      //  gtk_container_add(GTK_CONTAINER(pWindow),scroll);
        gtk_box_pack_start(GTK_BOX(pVbox),scroll,TRUE,TRUE,0);

        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),GTK_POLICY_ALWAYS,GTK_POLICY_ALWAYS);
        gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll),Image);
        



        //affichage
        gtk_widget_show_all(pWindow);

        //demarrer la boucle evenementielle
        gtk_main();

        printf("Merci pour votre attention!!!\n");

        return EXIT_SUCCESS;

}

void zoomin(GtkWidget *pWidget, gpointer data)
{
    GdkPixbuf *Src, *Dest;
    gint width, height;

    Src = gtk_image_get_pixbuf(GTK_IMAGE(data));

    width = gdk_pixbuf_get_width(Src);
    height = gdk_pixbuf_get_height(Src);

    Dest = gdk_pixbuf_scale_simple(Src,width+1000,height+1000,GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(data),Dest);

    g_object_unref(Dest);


}

void zoomout(GtkWidget *pWidget, gpointer data)
{
    GdkPixbuf *Src, *Dest;
    gint width, height;
    Src = gtk_image_get_pixbuf(GTK_IMAGE(data));
    width = gdk_pixbuf_get_width(Src);
    height = gdk_pixbuf_get_height(Src);

    Dest = gdk_pixbuf_scale_simple(Src,width-500,height-500,GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(data),Dest);

    g_object_unref(Dest);

}
