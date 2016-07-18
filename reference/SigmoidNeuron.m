classdef SigmoidNeuron < hgsetget
	properties
        inweights
        bias
    end
    methods
        function obj = SigmoidNeuron(w, b)
            obj.inweights = w;
            obj.bias = b;
        end
        function r = calcSigmoidNeuron(nn, in)
            if length(in) ~= length(nn.inweights)
                error('In values do not match weights');
            end
            z = -nn.bias;
            for i = 1:length(in)
                z = z + in(i)*nn.inweights(i);
            end
            r = 1/(1+(exp(1)^(-3.1*z)));
        end
        function n = mateSigmoidNeuron(a, b, threshold)
            if nargin < 3
                threshold = 0.51337;
            end
            if length(a.inweights) ~= length(b.inweights)
                error('Incompatible parents');
            end
            n = SigmoidNeuron(a.inweights, a.bias);
            for i = 1:length(a.inweights)
                if rand() > threshold
                     n.inweights(i) = b.inweights(i);
                end
            end
            if rand() > threshold
                n.bias = b.bias;
            end
        end
        function m = mutateSigmoidNeuron(a, threshold, maxweight, maxbias)
            m = SigmoidNeuron(a.inweights, a.bias);
            for i = 1:length(a.inweights)
                if rand() > threshold
                    m.inweights(i) = floor(mod(rand()*(10*ceil(log10(maxweight+1))), maxweight+1));
                end
            end
            if rand() > threshold
                m.bias = floor(mod(rand()*(10*ceil(log10(maxbias+1))), maxbias+1));
            end
        end
    end
end