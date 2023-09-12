#include <QCoreApplication>
#include <QLowEnergyServer>
#include <QLowEnergyService>
#include <QLowEnergyCharacteristicData>
#include <QLowEnergyDescriptorData>
#include <QBluetoothUuid>

class BleServer : public QObject
{
    Q_OBJECT

public:
    BleServer(QObject* parent = nullptr)
        : QObject(parent), server(nullptr), customService(nullptr)
    {
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QCoreApplication app(argc, argv);

        QLowEnergyAdvertisingParameters advertisingParameters;
        advertisingParameters.setDiscoverability(QLowEnergyAdvertisingParameters::DiscoverabilityGeneral);
        advertisingParameters.setMode(QLowEnergyAdvertisingParameters::Balanced);

        server = new QLowEnergyServer(this);
        
        // Özel bir hizmet oluşturun
        customService = server->addService(QBluetoothUuid(0x1801)); // Örnek bir özel hizmet UUID'si kullanıyoruz

        // Özel bir karakteristik ekleyin
        QLowEnergyCharacteristicData customCharacteristicData;
        customCharacteristicData.setUuid(QBluetoothUuid(0x2A05)); // Örnek bir özel karakteristik UUID'si kullanıyoruz
        customCharacteristicData.setValue(QByteArray(1, 0)); // Örnek bir başlangıç değeri
        customCharacteristicData.setProperties(QLowEnergyCharacteristic::Read | QLowEnergyCharacteristic::Write);
        
        // Özel bir karakteristik oluşturun
        customCharacteristic = customService->addCharacteristic(customCharacteristicData);

        // Özel bir açıklama ekleyin
        QLowEnergyDescriptorData descriptorData;
        descriptorData.setUuid(QBluetoothUuid(0x2901)); // Örnek bir açıklama UUID'si kullanıyoruz
        descriptorData.setValue("Özel Karakteristik Açıklama");

        // Karakteristiğe açıklamayı ekleyin
        customCharacteristic->addDescriptor(descriptorData);

        connect(server, &QLowEnergyServer::clientConnected, this, &BleServer::clientConnected);
        connect(server, &QLowEnergyServer::clientDisconnected, this, &BleServer::clientDisconnected);

        if (server->listen(advertisingParameters) == QLowEnergyServer::NoError) {
            qDebug() << "BLE server is running.";
        } else {
            qDebug() << "Failed to start BLE server.";
        }
    }

public slots:
    void clientConnected(QLowEnergyConnectionParameters params)
    {
        QLowEnergyController* controller = qobject_cast<QLowEnergyController*>(sender());
        if (!controller)
            return;

        qDebug() << "Client connected:" << controller->remoteAddress().toString();

        // Handle client connection here.
    }

    void clientDisconnected()
    {
        QLowEnergyController* controller = qobject_cast<QLowEnergyController*>(sender());
        if (!controller)
            return;

        qDebug() << "Client disconnected:" << controller->remoteAddress().toString();

        // Handle client disconnection here.
    }

private:
    QLowEnergyServer* server;
    QLowEnergyService* customService;
    QLowEnergyCharacteristic* customCharacteristic;
};

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    BleServer bleServer;
    return app.exec();
}

#include "main.moc"
