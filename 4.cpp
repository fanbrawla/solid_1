#include <iostream>
#include <memory>
#include <string>

class AbstractEntity {
public:
    virtual ~AbstractEntity() = default;
    virtual std::string GetType() const = 0; 
};

class AccountEntity : public AbstractEntity {
public:
    std::string GetType() const override {
        return "AccountEntity";
    }
};

class RoleEntity : public AbstractEntity {
public:
    std::string GetType() const override {
        return "RoleEntity";
    }
};

class IRepository {
public:
    virtual ~IRepository() = default;
    virtual void Save(const std::shared_ptr<AbstractEntity>& entity) = 0;
};

class AccountRepository : public IRepository {
public:
    void Save(const std::shared_ptr<AbstractEntity>& entity) override {
        if (entity->GetType() == "AccountEntity") {
            std::cout << "Saving AccountEntity" << std::endl;
        } else {
            std::cout << "Invalid entity type for AccountRepository" << std::endl;
        }
    }
};

class RoleRepository : public IRepository {
public:
    void Save(const std::shared_ptr<AbstractEntity>& entity) override {
        if (entity->GetType() == "RoleEntity") {
            std::cout << "Saving RoleEntity" << std::endl;
        } else {
            std::cout << "Invalid entity type for RoleRepository" << std::endl;
        }
    }
};

class RepositoryManager {
private:
    std::shared_ptr<IRepository> accountRepository;
    std::shared_ptr<IRepository> roleRepository;

public:
    RepositoryManager()
        : accountRepository(std::make_shared<AccountRepository>()),
          roleRepository(std::make_shared<RoleRepository>()) {}

    void Save(const std::shared_ptr<AbstractEntity>& entity) {
        if (entity->GetType() == "AccountEntity") {
            accountRepository->Save(entity);
        } else if (entity->GetType() == "RoleEntity") {
            roleRepository->Save(entity);
        } else {
            std::cout << "Unknown entity type" << std::endl;
        }
    }
};

int main() {
    auto accountEntity = std::make_shared<AccountEntity>();
    auto roleEntity = std::make_shared<RoleEntity>();

    RepositoryManager repositoryManager;

    repositoryManager.Save(accountEntity); 
    repositoryManager.Save(roleEntity);    

    return 0;
}