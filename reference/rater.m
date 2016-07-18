function r = rater(net, maze)
    keepRunning = 1;
    score = 0;
    currLoc = [1 1];
    % traverse the maze
    while keepRunning
        score = score + 1;
        keepRunning = 0;
        data = getLocation(currLoc);
        results = rot90([runNeuralNet(net, data); [1 2 3 4]]);
        results = sortrows(results, [-1 2]);
        dir = [0 0 0 0];
        dir(results(1,2)) = 1;
        
        % movement code
        % 1 = up, 2 = right, 3 = down, 4 = left
        if dir(1) == 1
            currLoc(2) = currLoc(2) - 1;
        elseif dir(2) == 1
            currLoc(1) = currLoc(1) + 1;
        elseif dir(3) == 1
            currLoc(2) = currLoc(2) + 1;
        elseif dir(4) == 1
            currLoc(1) = currLoc(1) - 1;
        end
        
        keepRunning = canMoveHere(currLoc);
    end
    r = score;
end