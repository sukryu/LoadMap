import { CloudResource } from "./CloudResource";

export class VirtualMachine extends CloudResource {
    private _cpu: number;
    private _memory: number;

    constructor(id: string, name: string, cpu: number, memory: number) {
        super(id, name);
        this._cpu = cpu;
        this._memory = memory;
    }

    get cpu(): number {
        return this._cpu;
    }

    get memory(): number {
        return this._memory;
    }

    async provision(): Promise<void> {
        this._status = 'provisioning';
        
        try {
            // 프로비저닝 시간을 시뮬레이션 (1-3초)
            const provisioningTime = Math.floor(Math.random() * 2000) + 1000;
            await new Promise(resolve => setTimeout(resolve, provisioningTime));
            
            // 20% 확률로 프로비저닝 실패 시뮬레이션
            if (Math.random() < 0.2) {
                throw new Error(`Failed to provision VM ${this.id}: Hardware allocation failed`);
            }
            
            this._status = 'running';
            console.log(`VM ${this.id} (${this.name}) successfully provisioned`);
        } catch (error) {
            this._status = 'stopped';
            throw error;
        }
    }
    
    async terminate(): Promise<void> {
        try {
            // 종료 시간을 시뮬레이션 (0.5-1.5초)
            const terminationTime = Math.floor(Math.random() * 1000) + 500;
            await new Promise(resolve => setTimeout(resolve, terminationTime));
            
            this._status = 'stopped';
            console.log(`VM ${this.id} (${this.name}) successfully terminated`);
        } catch (error: any) {
            throw new Error(`Failed to terminate VM ${this.id}: ${error.message}`);
        }
    }
}