# BLE on ESP32: Example for how to use many characteristics and notifications
It is not very straightforward to use many notifications and characteristics on the ESP32. Therefore, here two examples:
* BLE_many_char_server/client show an example of how to use many characteristics on the ESP32. However, it must be noted that the number of Notify receivers on the ESP32 is limited to 4. 
* BLE_many_notify_workaround_server/client show a work-around of how you can get "notification-like" functionality on the ESP32. Basically the trick is use a single notification that indicates through an INT which parameter is to be read. Then this can be passed to the main loop with a volatile bool that triggers read-out.

Explanation for the Code:
https://www.youtube.com/watch?v=zxs__8CykDA
