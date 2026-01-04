#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/compressed_image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

class CameraProxyNode : public rclcpp::Node {
public:
    CameraProxyNode() : Node("camera_proxy") {
        // Ustawienie QoS na BestEffort (SensorData)
        auto qos = rclcpp::SensorDataQoS();

        // Standardowy publisher (lepiej zarządza Shared Memory niż niektóre wersje image_transport)
        pub_ = this->create_publisher<sensor_msgs::msg::Image>("image_topic", qos);

        sub_ = this->create_subscription<sensor_msgs::msg::CompressedImage>(
            "/oak/rgb/image_raw/compressed", qos,
            std::bind(&CameraProxyNode::imageCallback, this, std::placeholders::_1)
        );

        RCLCPP_INFO(this->get_logger(), "Proxy Node wystartował z profilem BestEffort.");
    }

private:
    void imageCallback(const sensor_msgs::msg::CompressedImage::SharedPtr msg) {
        try {
            // 1. Dekodowanie (operacja ciężka)
            cv::Mat img = cv::imdecode(cv::Mat(msg->data), cv::IMREAD_COLOR);
            if (img.empty()) return;

            // 2. Tworzenie wiadomości
            auto ros_img = std::make_unique<sensor_msgs::msg::Image>();
            
            // Minimalizacja kopiowania przez cv_bridge
            cv_bridge::CvImage cv_img(msg->header, "bgr8", img);
            cv_img.toImageMsg(*ros_img);

            // 3. Publikacja (Shared Memory zadziała automatycznie, jeśli subskrybent jest lokalny)
            pub_->publish(std::move(ros_img));

        } catch (const std::exception & e) {
            RCLCPP_ERROR(this->get_logger(), "Błąd: %s", e.what());
        }
    }

    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr pub_;
    rclcpp::Subscription<sensor_msgs::msg::CompressedImage>::SharedPtr sub_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    // Używamy SingleThreadedExecutor, ale w przyszłości można zmienić na StaticSingleThreaded
    rclcpp::spin(std::make_shared<CameraProxyNode>());
    rclcpp::shutdown();
    return 0;
}