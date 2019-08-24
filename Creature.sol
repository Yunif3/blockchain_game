pragma solidity ^0.4.24;

contract Test {

    enum Types { fire, water, air, earth }
    
    struct Creature {
        string nickname;
        Types attribute;
        uint256 power;
        bool breeding;
        bool tradeable;
        uint256 TokenId;
    }
    
    uint256 TokenId = 0;
    mapping(address => Creature[]) creatures;
    mapping(uint256 => address) owners;
    mapping(uint256 => bool) private tokenExists;
    
    function createCreature(string memory nick, Types t, uint256 p, bool b, bool trade) public{
        creatures[msg.sender].push(Creature(nick, t, p, b, trade, TokenId));
        owners[TokenId] = msg.sender;
        tokenExists[TokenId] = true;
        TokenId++;
    }
    
    function random() private view returns (uint256) {
       return uint256(keccak256(block.timestamp, block.difficulty));
    }
   
    function createRandomCreature(string memory nick, bool trade) public{
        bool b = true;
        if (random() % 2 == 0) {
            b = false;
        }
        createCreature(nick, Types(random()%4), random()%10000, b, trade);
    }
    
    // ERC20 compatible functions
    function name() public view returns (string memory name) {
        return "CreatureToken";
    }
    
    function symbol() public view returns (string memory symbol) {
         return "CRT";
    }
    
    uint256 private total_supply = 1000;
    function totalSupply() public view returns (uint256 supply) {
        return total_supply;
    }

    function balanceOf(address _owner) public view returns (uint balance) {
        return creatures[_owner].length;
    }
    
    // Functions that define ownership

    function ownerOf(uint256 _tokenId) constant returns (address owner) {
        require(tokenExists[_tokenId]);
        return owners[_tokenId];
    }
    
    mapping(address => mapping (address => uint256)) allowed;
    function approve(address _to, uint256 _tokenId) {
        require(msg.sender == ownerOf(_tokenId));
        require(msg.sender != _to);
        allowed[msg.sender][_to] = _tokenId;
        Approval(msg.sender, _to, _tokenId);
    }
    
    function find_index(address owner, uint256 _tokenId) view returns(uint256 index) {
        require(tokenExists[_tokenId]);
        require(owners[_tokenId] == owner);
        for (uint256 i = 0; i < balanceOf(owner); ++i) {        
            if (creatures[owner][i].TokenId == _tokenId) {
                return i;
            }
        }
    }
    
    function remove(address owner, uint256 index) view {
        creatures[owner][index] = creatures[owner][balanceOf(owner) - 1];
        delete creatures[owner][balanceOf(owner) - 1];
    }
    
    function takeOwnership(uint256 _tokenId) {
        require(tokenExists[_tokenId]);
        address oldOwner = ownerOf(_tokenId);
        address newOwner = msg.sender;
        require(newOwner != oldOwner);
        require(allowed[oldOwner][newOwner] == _tokenId);
        owners[_tokenId] = newOwner;
        uint256 index = find_index(oldOwner, _tokenId);
        Creature c = creatures[oldOwner][index];
        creatures[newOwner].push(c);
        remove(oldOwner, index);
        Transfer(oldOwner, newOwner, _tokenId);
    }
    
    function removeFromTokenList(address owner, uint256 _tokenId) private {
       uint256 index = find_index(owner, _tokenId);
       remove(owner, index);
    }
    
    function transfer(address _to, uint256 _tokenId){
        address currentOwner = msg.sender;
        address newOwner = _to;
        require(tokenExists[_tokenId]);
        require(currentOwner == ownerOf(_tokenId));
        require(currentOwner != newOwner);
        require(newOwner != address(0));
        uint256 index = find_index(currentOwner, _tokenId);
        Creature c = creatures[currentOwner][index];
        creatures[newOwner].push(c);
        remove(currentOwner, index);
        Transfer(currentOwner, newOwner, _tokenId);
    }
    
    function tokenOfOwnerByIndex(address _owner, uint256 _index) constant returns (uint256 _tokenId) {
        return creatures[_owner][_index].TokenId;
    }
    
    // Events
    
    event Transfer(address indexed _from, address indexed _to, uint256 _tokenId);
    
    event Approval(address indexed _owner, address indexed _approved, uint256 _tokenId);
}