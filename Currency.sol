pragma solidity ^0.4.24;

contract Currency {
    mapping(address => uint256) balances;
    mapping(address => mapping (address => uint256)) allowed;
    
    function createCurrency(uint256 amt) public {
        balances[msg.sender] += amt;
    }
    
    uint256 total = 1000;
    function totalSupply() public view returns (uint256 total) {
      return total;
    }
    
    function balanceOf(address tokenOwner) public view returns (uint) {
      return balances[tokenOwner];
    }
    
    function transfer(address receiver, uint numTokens) public returns (bool) {
      require(numTokens <= balances[msg.sender]);
      balances[msg.sender] = balances[msg.sender] - numTokens;
      balances[receiver] = balances[receiver] + numTokens;
      emit Transfer(msg.sender, receiver, numTokens);
      return true;
    }
    
    function approve(address delegate, uint numTokens) public returns (bool) {
      allowed[msg.sender][delegate] = numTokens;
      emit Approval(msg.sender, delegate, numTokens);
      return true;
    }
    
    function allowance(address owner, address delegate) public view returns (uint) {
      return allowed[owner][delegate];
    }
    
    function transferFrom(address owner, address buyer, uint numTokens) public returns (bool) {
      require(numTokens <= balances[owner]);
      require(numTokens <= allowed[owner][msg.sender]);
      balances[owner] = balances[owner] - numTokens;
      allowed[owner][msg.sender] = allowed[owner][msg.sender] - numTokens;
      balances[buyer] = balances[buyer] + numTokens;
      Transfer(owner, buyer, numTokens);
      return true;
    }
    
    // Events
    
    event Transfer(address indexed _from, address indexed _to, uint256 amount);
    
    event Approval(address indexed _owner, address indexed _approved, uint256 amount);
}