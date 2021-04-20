  #include "ros/ros.h"
  #include "std_msgs/Char.h"
   
   //explicación nodo subscriber sencillo 

   /*la función se llamará cuando llegue un nuevo mensaje en el topic chatter*/

   void chatterCallback(const std_msgs::Char::ConstPtr& car)
   {
     ROS_INFO("I heard: [%c]", car->data);
   }
   
   int main(int argc, char **argv)
   {
     
     /*se inicia el nodo esta vez el nodo se llama listener*/	

     ros::init(argc, argv, "nodeH");
   
     /*se inicia la comunicación con el sistema ROS*/

     ros::NodeHandle h;

	/*se crea un objeto tipo subscriber, con la funcion .subscribe se retorna un objeto de este tipo y se especifica el nombre del topic, 		el tamaño del buffer que guarda los mensajes si estos se reciben mas rápido de lo que se pueden procesar y se llama la función creada 		al principio indicando que se recibió un mensaje nuevo*/
   
          ros::Subscriber subEH = h.subscribe("chatE2H", 1000, chatterCallback);
          ros::Subscriber subFH = h.subscribe("chatF2H", 1000, chatterCallback);
          ros::Subscriber subGH = h.subscribe("chatG2H", 1000, chatterCallback);
   
     /*realiza el callback al nodo publisher*/
     
     ros::spin();
   
     return 0;
   }
