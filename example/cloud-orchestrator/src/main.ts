import { Database } from "./models/Database";
import { LoadBalancer } from "./models/LoadBalancer";
import { VirtualMachine } from "./models/VirtualMachine";
import { ResourceManager } from "./services/ResourceManager";

async function main() {
    const resourceManager = new ResourceManager();

    // 각각의 리소스 생성
    const vm = new VirtualMachine("vm-001", "WebServer", 4, 8);
    const lb = new LoadBalancer("lb-001", "FrontendLB", "round-robin");
    const db = new Database("db-001", "UserDB", "PostgreSQL", 100);

    // 리소스 매니저에 추가
    resourceManager.addResource(vm);
    resourceManager.addResource(lb);
    resourceManager.addResource(db);

    // 모두 provision
    resourceManager.provisionAll();

    // 모두 terminate
    resourceManager.terminateAll();

    // 리소스 삭제
    resourceManager.removeResource("vm-001");
}

main();