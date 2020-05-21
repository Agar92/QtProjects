#include <QtWidgets>
#include <QtConcurrent>

#include <functional>

/*
#include <iostream>
#include <future>
*/

using namespace QtConcurrent;

#ifdef PRIME
bool is_prime (int x) {
  std::cout << "Calculating. Please, wait...\n";
  for (int i=2; i<x; ++i) if (x%i==0) return false;
  return true;
}
#endif

int main(int argc, char **argv)
{
#ifdef PRIME
    // call function asynchronously:
    int num = 444444443;
    std::future<bool> fut = std::async(is_prime, num);
    // do something while waiting for function to set future:
    std::cout << "checking, please wait";
    std::chrono::milliseconds span (100);
    while (fut.wait_for(span)==std::future_status::timeout)
      std::cout << '.' << std::flush;
    bool x = fut.get();     // retrieve return value
    std::cout << "\n" + std::to_string(num) + " " << (x?"is":"is not") << " prime.\n";
    for(int i=0; i<iterations; ++i) spin(i);
#endif

    QApplication app(argc, argv);
    const int iterations = 50;
    // Prepare the vector.
    QVector<int> vector;
    for (int i = 0; i < iterations; ++i) vector.append(i);
    // Create a progress dialog.
    QProgressDialog dialog;
    dialog.setLabelText(QString("Progressing using %1 thread(s)...").arg(QThread::idealThreadCount()));
    // Create a QFutureWatcher and connect signals and slots.
    QFutureWatcher<void> futureWatcher;
    QObject::connect(&futureWatcher, &QFutureWatcher<void>::finished, &dialog, &QProgressDialog::reset);
    QObject::connect(&dialog, &QProgressDialog::canceled, &futureWatcher, &QFutureWatcher<void>::cancel);
    QObject::connect(&futureWatcher,  &QFutureWatcher<void>::progressRangeChanged, &dialog, &QProgressDialog::setRange);
    QObject::connect(&futureWatcher, &QFutureWatcher<void>::progressValueChanged,  &dialog, &QProgressDialog::setValue);
    // Function to compute:
    std::function<void(int&)> spin = [](int &iteration) {
        const int work = 1000 * 1000 * 50;
        volatile int v = 0;
        for (int j = 0; j < work; ++j)
            ++v;

        qDebug() << "iteration" << iteration << "in thread" << QThread::currentThreadId();
    };
    // Start the computation.
    futureWatcher.setFuture(QtConcurrent::map(vector, spin));
    // Display the dialog and start the event loop.
    dialog.exec();
    futureWatcher.waitForFinished();
    // Query the future to check if was canceled.
    qDebug() << "Canceled?" << futureWatcher.future().isCanceled();

}
