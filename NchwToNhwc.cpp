#include <iostream>
#include <vector>

void* convertNCHWtoNHWC(const void* voidPointer, const std::vector<int>& shapeNCHW) {
    const float* dataNCHW = static_cast<const float*>(voidPointer);

    int N = shapeNCHW[0];
    int C = shapeNCHW[1];
    int H = shapeNCHW[2];
    int W = shapeNCHW[3];

    int sizeNHWC = N * H * W * C;
    float* dataNHWC = new float[sizeNHWC];

    for (int n = 0; n < N; ++n) {
        for (int h = 0; h < H; ++h) {
            for (int w = 0; w < W; ++w) {
                for (int c = 0; c < C; ++c) {
                    int nhwc_index = n * H * W * C + h * W * C + w * C + c;
                    int nchw_index = n * C * H * W + c * H * W + h * W + w;
                    dataNHWC[nhwc_index] = dataNCHW[nchw_index];
                }
            }
        }
    }

    return dataNHWC;
}

int main() {
    // Test için örnek veri ve boyutları
    float dataNCHW[] = { /* veri burada olacak */ };
    int N = 1, C = 96, H = 8, W = 8;
    std::vector<int> shapeNCHW = {N, C, H, W};

    // Dönüştürülen veriyi almak için void* pointer oluştur
    void* outputPointer = convertNCHWtoNHWC(dataNCHW, shapeNCHW);

    // Elde edilen veriyi ekrana yazdıralım
    float* outputData = static_cast<float*>(outputPointer);
    for (int n = 0; n < N; ++n) {
        for (int h = 0; h < H; ++h) {
            for (int w = 0; w < W; ++w) {
                for (int c = 0; c < C; ++c) {
                    int nhwc_index = n * H * W * C + h * W * C + w * C + c;
                    std::cout << outputData[nhwc_index] << " ";
                }
            }
        }
    }

    // Dönüştürülen verinin kullanımı tamamlandıktan sonra bellek alanını serbest bırak
    delete[] outputData;

    return 0;
}
