import { CloudResource } from "./CloudResource";

export type LoadBalancerAlgorithms = "round-robin" | "least-connections";

export class LoadBalancer extends CloudResource {
    private _algorithm: LoadBalancerAlgorithms;

    constructor(id: string, name: string, algorithm: LoadBalancerAlgorithms) {
        super(id, name);
        this._algorithm = algorithm;
    }

    get algorithm(): LoadBalancerAlgorithms {
        return this._algorithm;
    }

    async provision(): Promise<void> {
        this._status = 'provisioning';
        
        try {
            const provisioningTime = Math.floor(Math.random() * 2000) + 1000;
            await new Promise(resolve => setTimeout(resolve, provisioningTime));
            
            if (Math.random() < 0.2) {
                throw new Error(`Failed to provision Load Balancer ${this.id}: Configuration failed`);
            }
            
            this._status = 'running';
            console.log(`Load Balancer ${this.id} (${this.name}) successfully provisioned with ${this._algorithm} algorithm`);
        } catch (error) {
            this._status = 'stopped';
            throw error;
        }
    }
    
    async terminate(): Promise<void> {
        try {
            const terminationTime = Math.floor(Math.random() * 1000) + 500;
            await new Promise(resolve => setTimeout(resolve, terminationTime));
            
            this._status = 'stopped';
            console.log(`Load Balancer ${this.id} (${this.name}) successfully terminated`);
        } catch (error: any) {
            throw new Error(`Failed to terminate Load Balancer ${this.id}: ${error.message}`);
        }
    }
}