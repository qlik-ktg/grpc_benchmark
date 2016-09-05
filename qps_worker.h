#ifndef QPS_WORKER_H_
#define QPS_WORKER_H_

#include <memory>

#include <grpc/support/atm.h>

namespace grpc {

class Server;

namespace testing {

class WorkerServiceImpl;

class QpsWorker {
public:
    explicit QpsWorker(int driver_port, int server_port = 0);
    ~QpsWorker();

    bool Done() const;
    void MarkDone();

private:
    std::unique_ptr<WorkerServiceImpl> impl_;
    std::unique_ptr<Server> server_;

    gpr_atm done_;
};

}  // namespace testing
}  // namespace grpc

#endif /* QPS_WORKER_H_ */
