import { CloudResource } from "../models/CloudResource";

export class ResourceManager {
    private resources: Map<string, CloudResource>;

    constructor() {
        this.resources = new Map<string, CloudResource>();
    }

    addResource(resource: CloudResource): void {
        this.resources.set(resource.id, resource);
    }

    removeResource(id: string): void {
        this.resources.delete(id);
    }

    listResources(): CloudResource[] {
        return Array.from(this.resources.values());
    }

    async provisionAll(): Promise<void> {
        const provisioningPromises = Array.from(this.resources.values()).map(
            resource => resource.provision()
        );
        await Promise.all(provisioningPromises);
    }

    async terminateAll(): Promise<void> {
        const terminationPromises = Array.from(this.resources.values()).map(
            resource => resource.terminate()
        );
        await Promise.all(terminationPromises);
    }
}